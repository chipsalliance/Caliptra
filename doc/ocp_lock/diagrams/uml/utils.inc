'
' This file has generic items needed by all OCP LOCK UML sequence diagrams
'
'
!if %not(%variable_exists("ocp_lock_inc"))
    !$ocp_lock_inc = %true()

    autonumber 1 1  "<b>[000]"

    !pragma teoz true

    box "Caliptra"
        participant "FW" as cfw
    end box

    box "Encryption engine"
        participant "SFR\nInterface" as sfr
        participant "Control" as ee
        participant "Key cache" as kc
    end box

    hide unlinked
!endif
