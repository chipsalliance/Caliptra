'
' This file has generic items needed by all OCP LOCK UML sequence diagrams
'
'
!if %not(%variable_exists("ocp_lock_inc"))
    !$ocp_lock_inc = %true()

    !$BUFFER_ACTIVATION = "#lightblue"

    !unquoted procedure $zeroize($who)
        cfw -> $who !! : Zeroize
        $who--
    !endprocedure

    !unquoted procedure $hpke_unwrap($ak_dest, $new_ak_dest)
        group HPKE Unwrap
            cfw -> hpke: Derive HPKE decryption key and IV
            cfw -> aes++: Decrypt access key
            cfw -> aes: Write encrypted access key, decryption key, and IV
            !if ($ak_dest != "cfw")
                aes -> $ak_dest **: Decrypt access key
                $ak_dest++ $BUFFER_ACTIVATION
            !else
                aes -> cfw: Decrypt access key
            !endif
            aes -> cfw: Done
            aes--

            !if ($new_ak_dest != "")
                cfw -> aes++: Decrypt new access key
                cfw -> aes: Write new-access-key ciphertext, decryption key, and IV
                aes -> $new_ak_dest **: Decrypt new access key
                $new_ak_dest++ $BUFFER_ACTIVATION
                aes -> cfw: Done
                aes--
            !endif
        end
    !endprocedure

    !unquoted procedure $preconditioned_key_extract($salt_name, $salt_from, $key_name, $key_from, $output_name, $output_to)
        group Preconditioned Key Extract
            cfw -> aes++: Compute salt checksum
            !if ($salt_from != "cfw")
                aes -> $salt_from: Read $salt_name
            !else
                cfw -> aes: Write $salt_name as salt
            !endif

            aes -> cfw: Write AES-ECB-Encrypt($salt_name, 0x0000...)
            aes -> cfw: Done
            aes--

            cfw -> hmac++: Derive preconditioned key
            cfw -> hmac: Write salt checksum as KDF context
            !if ($key_from != "cfw")
                hmac -> $key_from: Read $key_name
            !else
                cfw -> hmac: Write $key_name
            !endif

            !if ($output_to != "mpk_secret")
                hmac -> $output_to ** : Write HMAC($key_name, [KDF label & context])
                $output_to++ $BUFFER_ACTIVATION
            !else
                ' Special-case for MPK secret, which already exists.
                hmac -> pkey **: Write HMAC($key_name, [KDF label & context])
                pkey++ $BUFFER_ACTIVATION
            !endif
            
            hmac -> cfw: Done
            hmac--

            cfw -> hmac++: Derive $output_name
            !if ($salt_from != "cfw")
                hmac -> $salt_from: Read $salt_name
            !else
                cfw -> hmac: Write $salt_name as salt
            !endif
            !if ($output_to != "mpk_secret")
                hmac -> $output_to: Read preconditioned key
            !else
                hmac -> pkey: Read preconditioned key
            !endif
            hmac -> $output_to: Write HMAC($salt_name, preconditioned key)
            hmac -> cfw: Done
            hmac--

            !if ($output_to == "mpk_secret")
                $zeroize(pkey)
            !endif
        end

    !endprocedure

    !unquoted procedure $preconditioned_aes_encrypt($secret, $key, $plaintext_name, $plaintext_from)
        group Preconditioned AES Encrypt
            cfw -> drbg: Get random 96-bit AES IV
            cfw -> drbg: Get random 64-bit AES salt

            cfw -> hmac++: Derive AES encryption key
            cfw -> hmac: Write AES salt
            hmac -> $secret: Read encryption secret
            hmac -> $key ** : Write HMAC(encryption secret, [KDF label & context])
            $key++ $BUFFER_ACTIVATION
            hmac -> cfw: Done
            hmac--

            !if ($secret != "enabled_mpk_encryption_secret")
                $zeroize($secret)
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

    !unquoted procedure $preconditioned_aes_decrypt($secret, $key, $ciphertext_name, $ciphertext_to)
        group Preconditioned AES Decrypt
            cfw -> hmac++: Derive AES decryption key
            cfw -> hmac: Write AES salt
            hmac -> $secret: Read encryption secret
            hmac -> $key ** : Write HMAC(encryption secret, [KDF label & context])
            $key++ $BUFFER_ACTIVATION
            hmac -> cfw: Done
            hmac--

            !if ($secret != "enabled_mpk_encryption_secret")
                $zeroize($secret)
            !endif

            cfw -> aes++: Decrypt $ciphertext_name
            cfw -> aes: Write $ciphertext_name, AAD, and IV
            aes -> $key: Read encryption key
            aes -> $ciphertext_to **: Write AES-GCM-Decrypt(encryption key, IV, AAD, ciphertext)
            $ciphertext_to++ $BUFFER_ACTIVATION
            aes -> cfw: Done
            aes--

            $zeroize($key)
        end
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
        participant "HPKE keypair" as hpke
        participant "Caliptra\nStable Key\n(Key Vault)" as c_stable_key
        participant "L.O.C.K.\nStable Key\n(Key Vault)" as l_stable_key
        participant "HEK Seed\n(Key Vault)" as hek_seed
        participant "Enabled MPK Encryption Secret\n(Key Vault)" as enabled_mpk_encryption_secret
        participant "HEK\n(Key Vault)" as hek
        participant "Preconditioned key\n(Key Vault)" as pkey
        participant "MPK Secret\n(Key Vault)" as mpk_secret
        participant "EPK\n(Key Vault)" as epk
        participant "MEK Secret Seed\n(Key Vault)" as mek_secret_seed
        participant "MEK Secret\n(Key Vault)" as mek_secret
        participant "Access key\n(Key Vault)" as kv_ak
        participant "New access key\n(Key Vault)" as kv_ak2
        participant "Encryption Secret\n(Key Vault)" as encryption_secret
        participant "New Encryption Secret\n(Key Vault)" as encryption_secret2
        participant "Encryption Key\n(Key Vault)" as encryption_key
        participant "MPK\n(Key Vault)" as mpk
        participant "New Encryption Key\n(Key Vault)" as encryption_key2
        participant "Enabled MPK Encryption Key\n(Key Vault)" as enabled_mpk_encryption_key
        participant "MEK\n(Key Vault)" as mek
    end box

    box "Encryption engine"
        participant "SFR\nInterface" as sfr
        participant "Control" as ee
        participant "Key cache" as kc
    end box

    hide unlinked
!endif
