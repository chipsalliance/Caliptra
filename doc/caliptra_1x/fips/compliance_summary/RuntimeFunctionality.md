# Runtime Functionality

*Ref: VE04.03.01; VE04.11.01; VE04.14.01; VE04.15.01; VE05.06.(01/02/03/04); VE05.07.01; VE10.15.(01/02); VE10.25.01; VE10.27.(01/02/03); VE10.28.(01/02); VE10.29.01; VE10.37.(01/02); VE10.53.01.(01/02); VE10.54.(01/02/03).*

Following transfer of execution to the Runtime code, the Module is in the AWAIT_CMD state, with all commands available within a [mailbox command dispatcher](https://github.com/chipsalliance/caliptra-sw/blob/rom-1.0.3/runtime/src/lib.rs#L144) [loop](https://github.com/chipsalliance/caliptra-sw/blob/rom-1.0.3/runtime/src/lib.rs#L235) of the following form:


<img src="../../Images/MailboxCommandDispatchLoop.png" width="600" height="400">

The Module provides the approved services as described in [Services and HMI](./ServicesAndHMI.md) and [FSM](./FSM.md). 

