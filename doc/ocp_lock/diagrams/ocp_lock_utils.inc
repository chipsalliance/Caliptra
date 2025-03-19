'
' This file has generic items needed by all OCP LOCK UML sequence diagrams
'
'
!if %not(%variable_exists("ocp_lock_inc"))
    !$ocp_lock_inc = %true()

    !if %not(%variable_exists("show_precond"))
        !$show_precond = %true()
    !endif
    !if %not(%variable_exists("show_title"))
        !$show_title = %true()
    !endif
    !if %not(%variable_exists("show_api"))
        !$show_api = %true()
    !endif
    !if %not(%variable_exists("show_msg_parsing"))
        !$show_msg_parsing = %true()
    !endif
    !if %not(%variable_exists("show_done"))
        !$show_done = %true()
    !endif

    !if %variable_exists("doc_gen")
        !$show_precond = %true()
        !$show_title = %true()
        !$show_api = %false()
        !$show_msg_parsing = %false()
        !$show_done = %true()
        !log doc gen exists
    !endif

	!$SYNC_COLOR = "#red"
	!$ASYNC_COLOR = "#green"
	!$BUFFER_ACTIVATION = "#lightblue"

	!$sync = "-[" + $SYNC_COLOR + "]>"
	!$return = "-[" + $SYNC_COLOR + "]->"
	!$async = "-[" + $ASYNC_COLOR + "]>>"
	!$sometimelater = "..."

	!unquoted procedure $self($who, $msg)
	   $who $sync $who : $msg
	   ||0||
	!endprocedure

    !if %not(%variable_exists($show_sometime_later))
        !$show_sometime_later = %true()
    !endif

	!unquoted procedure $sometimelater()
        !if ($show_sometime_later)
           ...
	       ||0||
        !endif
	!endprocedure

	autonumber 1 1  "<b>[000]"

	!pragma teoz true

    participant "Remote Key\nManagement Service" as rkms


    participant "Host" as host


    participant "Storage\nDevice\nFW" as fw

    box "Caliptra"
    	participant "Mail Box" as mb
    	participant "ROM" as crom
    	participant "FW" as cfw
    	participant "ROM to FW\nHandoff Data" as hoff
        participant "DRBG" as rand
        participant "DMA Engine" as dma
        participant "Key Vault" as kv
        participant "Key Vault\nFuses" as fuses
        participant "Key Vault\nStorage Root Key" as gsrk
        participant "Key Vault\nSlot A\n(Storage Root Key)" as srk
        participant "Key Vault\nSlot B\n(PMEK Secret)" as pmeks
        participant "Key Vault\nSlot F\n(DICE Alias Key)\necdsa_secp384r1_sha384" as dice
        participant "Key Vault\nSlot G\n(KEM Keypair)" as kemg
        participant "Key Vault\nSlot W\n(Temporary)" as tempw
        participant "Key Vault\nSlot X\n(MEK Seed)" as meks
        participant "Key Vault\nSlot Y\n(Temporary)" as tempy
        participant "Key Vault\nSlot Z\n(Temporary)" as tempz
        participant "Key Vault\nTemp Memory" as tempmem
    end box

    box "Encryption Engine"
        participant "SFR\nInterface" as sfr
        participant "Control" as ee
        participant "Key Cache" as kc
    end box

    box "Media"
        participant "Create new\Storage Root Key\non NVM subsystem reset" as csrk
        participant "Destroy all\Storage Root Keys\non NVM subsystem reset" as dsrk
    end box

    hide unlinked
	footer Filename: %filename()

	header Version 1
!endif

