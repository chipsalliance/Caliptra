*Ref: VE03.07.01, VE03.07.02*

As summarized in the [Caliptra documentation Runtime Firmware Main loop](https://github.com/chipsalliance/caliptra-sw/blob/main/runtime/README.md#main-loop) section of documentation, the Caliptra mailbox command interface is a blocking interface that does not permit concurrent operators: callers must wait until Caliptra is no longer busy to call a mailbox command. As such, data output is inhibited until a given command is completed in all situations. The mailbox interface is not available until self-test has completed or if the Caliptra block is in an error state.

However, the SHA accelerator engine may be accessed semi-independently (coordinated via the API), hence the overall module is considered to permit concurrent operation.

The Module does not implement manual entry.
