'
' This file has generic items needed by all OCP LOCK UML sequence diagrams
'
'
!if %not(%variable_exists("ocp_lock_inc"))
    !$ocp_lock_inc = %true()

    !unquoted procedure $activate($who)
        $who++ #lightblue
    !endprocedure

    !unquoted procedure $activate_kv($who)
        $who++ #lightgreen
    !endprocedure

    !unquoted procedure $zeroize($who)
        cfw -> $who !! : Zeroize
        $who--
    !endprocedure

    !unquoted procedure $kdf($who, $key_name, $key_from, $label, $output_name, $output_to)
        $who -> hmac++: Derive $output_name
        $who -> hmac: Write $label as KDF label/context
        hmac -> $key_from: Read $key_name

        !if ($output_to == "dkey")
            ' Don't create dkey, it is used across multiple operations.
            hmac -> $output_to: Write HMAC($key_name, [KDF label & context])
        !else
            hmac -> $output_to ** : Write HMAC($key_name, [KDF label & context])
        !endif
        $activate_kv($output_to)
        hmac -> $who: Done
        hmac--
    !endprocedure

    !unquoted procedure $hpke_unwrap($ak_dest, $new_ak_dest)
        group HPKE Unwrap
            cfw -> hpke: Get HPKE public key
            !if ($new_ak_dest != "")
                cfw -> cfw: Derive HPKE decryption keys and IVs
            !else
                cfw -> cfw: Derive HPKE decryption key and IV
            !endif
            cfw -> aes++: Decrypt access key
            cfw -> aes: Write ciphertext, decryption key, and IV
            aes -> $ak_dest **: Decrypt access key
            $activate($ak_dest)
            aes -> cfw: Done
            aes--

            !if ($new_ak_dest != "")
                cfw -> aes++: Decrypt new access key
                cfw -> aes: Write new-access-key ciphertext, decryption key, and IV
                aes -> $new_ak_dest **: Decrypt new access key
                $activate($new_ak_dest)
                aes -> cfw: Done
                aes--
            !endif
        end
    !endprocedure

    !unquoted procedure $preconditioned_key_extract($salt_name, $salt_from, $key_name, $key_from, $output_name, $output_to)
        group Preconditioned Key Extract
            cfw -> aes++: Compute salt checksum
            aes -> $salt_from: Read $salt_name
            aes -> cfw: Write AES-ECB-Encrypt($salt_name, 0x0000...)
            aes -> cfw: Done
            aes--

            $kdf(cfw, $key_name, $key_from, salt checksum, preconditioned key, dkey)

            cfw -> hmac++: Derive $output_name
            hmac -> $salt_from: Read $salt_name
            hmac -> dkey: Read preconditioned key
            hmac -> $output_to **: Write HMAC($salt_name, preconditioned key)
            $activate_kv($output_to)
            hmac -> cfw: Done
            hmac--

            $zeroize(dkey)
        end

    !endprocedure

    !unquoted procedure $preconditioned_aes_encrypt($key, $subkey, $plaintext_name, $plaintext_from)
        group Preconditioned AES Encrypt
            cfw -> drbg: Get random 96-bit AES IV
            cfw -> drbg: Get random 64-bit AES salt

            $kdf(cfw, encryption key, $key, AES salt, AES encryption subkey, $subkey)

            !if ($key != "enabled_mpk_encryption_key")
                $zeroize($key)
            !endif

            cfw -> aes++: Encrypt $plaintext_name

            !if ($plaintext_from == "cfw")
                cfw -> aes: Write $plaintext_name, AAD, and IV
            !else
                cfw -> aes: Write AAD and IV
                aes -> $plaintext_from: Read $plaintext_name
            !endif

            aes -> $key: Read encryption key
            aes -> cfw: Write AES-GCM-Encrypt(encryption key, IV, AAD, plaintext)
            aes -> cfw: Done
            aes--

            !if ($plaintext_from != "cfw")
                $zeroize($plaintext_from)
            !endif

            $zeroize($key)
        end
    !endprocedure

    !unquoted procedure $preconditioned_aes_decrypt($key, $subkey, $ciphertext_name, $ciphertext_to)
        group Preconditioned AES Decrypt
            $kdf(cfw, encryption key, $key, AES salt, AES decryption subkey, $subkey)

            !if ($key != "enabled_mpk_encryption_key")
                $zeroize($key)
            !endif

            cfw -> aes++: Decrypt $ciphertext_name
            cfw -> aes: Write $ciphertext_name, AAD, and IV
            aes -> $key: Read encryption key
            !if ($ciphertext_to != "cfw")
                aes -> $ciphertext_to **: Write AES-GCM-Decrypt(encryption key, IV, AAD, ciphertext)
                $activate($ciphertext_to)
            !else
                aes -> $ciphertext_to: Write AES-GCM-Decrypt(encryption key, IV, AAD, ciphertext)
            !endif
            aes -> cfw: Done
            aes--

            $zeroize($key)
        end
    !endprocedure

    !unquoted procedure $program_mek()
        cfw -> sfr : Read Control Reg

        alt (DN == 1b || ERR == 1b || EXE == 1b)
            cfw -> sfr : Write Control Reg (DN = 1b)

            cfw -> cfw : Start timeout
            cfw -> sfr : Read Control Reg
            group loop until (rdy_timeout or (DN == 0b && ERR == 0b && EXE == 0b))
                cfw -> sfr : Read Control Reg
            end
        end

        group in any order
            cfw -> dma++ : MEK Write
            dma -> mek : Read MEK
            dma -> sfr : Write MEK
            note left sfr
                If the MEK is larger than the encryption engine requires,
                then the encryption engine truncates the MEK
            end note
            dma -> cfw-- : complete

            cfw -> sfr : Write Aux
            cfw -> sfr : Write Metadata
        end

        cfw -> sfr : Write Control Reg (CMD = Load_MEK, DN = 0, EXE = 1)
        cfw -> cfw : Start timeout

        group in any oder
            ee -> sfr : Read MEK
            ee -> sfr : Read AUX
            ee -> sfr : Read Metadata
        end

        ee -> kc : Store MEK

        group loop until (cmd_timeout or DN = 1b)
            ee -> sfr-- : Write Control Reg\n(DN = 1b,\n ERR = 0b,\n EXE = 0b)
            cfw -> sfr : Read Control Reg
        end
        sfr--

        cfw -> sfr : Write Control Reg (DN = 1b)
        note left sfr: Reset the SFR interface for next operation - not waiting for response
    !endprocedure

    autonumber 1 1  "<b>[000]"

    !pragma teoz true

    participant "Storage\nDevice\nFW" as dfw

    box "Caliptra"
        participant "ROM" as crom
        participant "FW" as cfw
        participant "DRBG" as drbg
        participant "DMA engine" as dma
        participant "HMAC engine" as hmac
        participant "AES engine" as aes
        participant "Fuses" as fuses
        participant "DICE UDS\n(Key Vault)" as uds
        participant "DICE IDevID CDI\n(Key Vault)" as idev
        participant "DICE Runtime Alias Key\n(Key Vault)" as dice
        participant "HPKE keypair\n(in memory)" as hpke
        participant "HEK\n(Key Vault)" as hek
        participant "MDK\n(Key Vault)" as mdk
        participant "Firmware DICE CDI\n(Key Vault)" as fw_cdi
        participant "Derived key\n(Key Vault)" as dkey
        participant "VEK\n(Key Vault)" as vek
        participant "MPK Secret\n(Key Vault)" as mpk_secret
        participant "SEK\n(in memory)" as sek
        participant "DPK\n(in memory)" as dpk
        participant "EPK\n(Key Vault)" as epk
        participant "MEK Secret Seed\n(Key Vault)" as mek_secret_seed
        participant "MEK Secret\n(Key Vault)" as mek_secret
        participant "Access key\n(in memory)" as ak
        participant "Current Access key\n(in memory)" as c_ak
        participant "New access key\n(in memory)" as n_ak
        participant "Encryption Key\n(Key Vault)" as encryption_key
        participant "Current Encryption Key\n(Key Vault)" as c_encryption_key
        participant "New Encryption Key\n(Key Vault)" as n_encryption_key
        participant "Encryption Subkey\n(Key Vault)" as encryption_subkey
        participant "Current Encryption Key\n(Key Vault)" as c_encryption_key
        participant "MPK\n(in memory)" as mpk
        participant "New Encryption Key\n(Key Vault)" as n_encryption_key
        participant "VEK Subkey\n(Key Vault)" as vek_subkey
        participant "MEK\n(Key Vault)" as mek

        ' Legend participants
        participant "Firmware-visible key\n(in memory)" as legend_fw_key
        participant "Key Vault key" as legend_kv_key
    end box

    box "Encryption engine"
        participant "SFR\nInterface" as sfr
        participant "Control" as ee
        participant "Key cache" as kc
    end box

    hide unlinked
!endif
