<p align="center">
  <img src="./images/ocp_page_1.jpg" alt="OCP Logo" />
</p>

**<p align="center">OCP Layered Open-Source Cryptographic Key-management (L.O.C.K.)</p>**

**<p align="center">NVMe™ Key Management Block</p>**

**<p align="center">Revision 0.8</p>**

**<p align="center">Version 0.8</p>**

**<p align="center">Date: April 2025</p>**

<div style="page-break-after: always"></div>

**Contributors**

<table>
<tr><td>Google</td><td>Microsoft</td><td>Samsung</td><td>Solidigm</td><td>Kioxia</td></tr>
<tr>
    <td>
        <ul>
            <li>Andrés Lagar-Cavilla</li>
            <li>Amber Huffman</li>
            <li>Charles Kuzman</li>
            <li>Jeff Andersen</li>
            <li>Chris Sabol</li>
            <li>Srini Narayanamurthy</li>
    </ul></td>
    <td>
        <ul>
            <li>Lee Prewitt</li>
            <li>Michael Norris</li>
            <li>Eric Eilertson</li>
            <li>Bryan Kelly</li>
            <li>Anjana Parthasarathy</li>
            <li>Ben Keen</li>
            <li>Bharat Pillilli</li>
    </ul></td>
    <td>
        <ul>
            <li>Jisoo Kim</li>
            <li>Gwangbae Choi</li>
            <li>Eric Hibbard</li>
            <li>Mike Allison</li>
    </ul></td>
    <td>
        <ul>
            <li>Scott Shadley</li>
            <li>Gamil Cain</li>
            <li>Festus Hategekimana</li>
    </ul></td>
    <td>
        <ul>
            <li>John Geldman</li>
            <li>Fred Knight</li>
            <li>Paul Suhler</li>
            <li>James Borden</li>
    </ul></td></tr>
</table>

**Revision Table**

| Date             | Revision # | Author              | Description |
| :--------------- | :--------- | :-----------------: | :---------- |
|  September 2024  |  0.5       | Authoring Companies | Initial proposal draft based on work from the list of contributors |
|    April 2025    |  0.7       | Authoring Companies | Updates that include updates APIs, UML Sequence diagrams, and racheting with fuses |

<div style="page-break-after: always"></div>

**License**

**Open Web Foundation (OWF) CLA**

Contributions to this Specification are made under the terms and conditions set forth in Open Web Foundation Modified Contributor License Agreement (“OWF CLA 1.0”) (“Contribution License”) by:

**Google, Microsoft, Samsung, Solidigm, Kioxia**

Usage of this Specification is governed by the terms and conditions set forth in **Open Web Foundation Modified Final Specification Agreement (“OWFa 1.0”) (“Specification License”)**.

You can review the applicable OWFa1.0 Specification License(s) referenced above by the contributors to this Specification on the OCP website at. For actual executed copies of either agreement, please contact OCP directly.

**Notes:**
1) The above license does not apply to the Appendix or Appendices. The information in the Appendix or Appendices is for reference only and non-normative in nature.

NOTWITHSTANDING THE FOREGOING LICENSES, THIS SPECIFICATION IS PROVIDED BY OCP "AS IS" AND OCP EXPRESSLY DISCLAIMS ANY WARRANTIES (EXPRESS, IMPLIED, OR OTHERWISE), INCLUDING IMPLIED WARRANTIES OF MERCHANTABILITY, NON-INFRINGEMENT, FITNESS FOR A PARTICULAR PURPOSE, OR TITLE, RELATED TO THE SPECIFICATION. NOTICE IS HEREBY GIVEN, THAT OTHER RIGHTS NOT GRANTED AS SET FORTH ABOVE, INCLUDING WITHOUT LIMITATION, RIGHTS OF THIRD PARTIES WHO DID NOT EXECUTE THE ABOVE LICENSES, MAY BE IMPLICATED BY THE IMPLEMENTATION OF OR COMPLIANCE WITH THIS SPECIFICATION. OCP IS NOT RESPONSIBLE FOR IDENTIFYING RIGHTS FOR WHICH A LICENSE MAY BE REQUIRED IN ORDER TO IMPLEMENT THIS SPECIFICATION. THE ENTIRE RISK AS TO IMPLEMENTING OR OTHERWISE USING THE SPECIFICATION IS ASSUMED BY YOU. IN NO EVENT WILL OCP BE LIABLE TO YOU FOR ANY MONETARY DAMAGES WITH RESPECT TO ANY CLAIMS RELATED TO, OR ARISING OUT OF YOUR USE OF THIS SPECIFICATION, INCLUDING BUT NOT LIMITED TO ANY LIABILITY FOR LOST PROFITS OR ANY CONSEQUENTIAL, INCIDENTAL, INDIRECT, SPECIAL OR PUNITIVE DAMAGES OF ANY CHARACTER FROM ANY CAUSES OF ACTION OF ANY KIND WITH RESPECT TO THIS SPECIFICATION, WHETHER BASED ON BREACH OF CONTRACT, TORT (INCLUDING NEGLIGENCE), OR OTHERWISE, AND EVEN IF OCP HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

**Acknowledgements**

The Contributors of this Specification would like to acknowledge the following companies for their feedback:

<div style="page-break-after: always"></div>

**Compliance with OCP Tenets**

Please describe how this Specification complies to the following OCP tenets. Compliance is required for at least three of the four tenets. The ideals behind open sourcing stipulate that everyone benefits when we share and work together. Any open source project is designed to promote sharing of design elements with peers and to help them understand and adopt those contributions. There is no purpose in sharing if all parties aren't aligned with that philosophy. The IC will look beyond the contribution for evidence that the contributor is aligned with this philosophy. The contributor actions, past and present, are evidence of alignment and conviction to all the tenets.

**Openness**

OCP L.O.C.K source for RTL and firmware will be licensed using the Apache 2.0 license. The specific mechanics and hosting of the code are work in progress due to CHIPS alliance timelines. Future versions of this spec will point to the relevant resources.

**Efficiency**

OCP L.O.C.K. is used to generate and load keys for use of encrypting user data prior to storing data at rest and decrypting stored user data at rest when read. So, it cannot yield a measurable impact on system efficiency.

**Impact**

OCP L.O.C.K. enables consistency and transparency to a foundational area of security of media encryption keys such that no firmware in the device ever has access to a media encryption key. Furthermore, no decrypted media encryption key exists in the device when power is removed from the device.

**Scale**

OCP L.O.C.K. is a committed intercept for Cloud silicon for Google and Microsoft. This scale covers both a significant portion of the Cloud market in hyperscale and enterprise.

**Sustainability**

The goal of OCP L.O.C.K. is to eliminate the need to destroy storage devices (e.g., SSDs) in the Cloud market by providing a mechanism that increases the confidence that a media encryption key within the device is deleted in a crypto-erase. This enables repurposing the device and or components on the device at end of use or end of life. Given the size of the Cloud market this provides a significant reduction of e-waste.

<div style="page-break-after: always"></div>

[[toc]]

# Introduction

OCP L.O.C.K. (Layered Open-source Cryptographic Key management) is a feature set conditionally compiled into Caliptra, which provides secure key management for Data-At-Rest protection in self-encrypting storage devices.

OCP L.O.C.K. was originally created as part of the Open Compute Project (OCP). The major revisions of the OCP L.O.C.K. specifications are published as part of Caliptra at OCP as OCP L.O.C.K. is an optional extension to Caliptra. The evolving source code and documentation for Caliptra are in the repository within the CHIPS Alliance Project, a Series of LF Projects, LLC.

# Background

OCP L.O.C.K is being defined to improve drive security. The life of a storage device in a datacenter is that the device leaves the supplier, a customer writes user data to the device, and then the device is decommissioned. The problem is that customer data is not allowed to leave the data center. There needs to be a high confidence that the storage device leaving the datacenter is secure. The current default cloud service provider (CSP) policy to ensure this level of security is to destroy the drive. Other policies may exist that leverage drive capabilities (e.g., Sanitize), but are not generally deemed inherently trustworthy by these CSPs[^1]. This produces significant e-waste and inhibits any re-use/recycling.

OCP L.O.C.K. is addressing these issues by:

* Preventing leakage of media keys via firmware vulnerabilities or side channels;
* Binding media keys to a set of securely-provisioned access keys; and
* Enabling attestable “hard” purge via erasure of fuse secrets.

## OCP L.O.C.K. goals

The goal of OCP L.O.C.K. is to define a Key Management Block (KMB) that:

- Isolates storage keys to a trusted hardware block
- Binds storage keys to a given set of externally-supplied access keys
- Provides replay-resistant transport security for these access keys such that they can be injected without trusting the host
- Uses a fuse epoch key (FEK) and controller epoch key (CEK) for sanitization
- Is able to be used in conjunction with the Opal[^2] and Key Per I/O[^3] storage device specifications

# Overview

Self-encrypting drives (SEDs) store data encrypted to media encryption keys (MEKs). SEDs include the following building blocks:

- The storage media that holds data at rest.
- An Encryption Engine that performs line-rate encryption and decryption of data as it enters and exits the drive.
- A controller that manages the lifecycle of MEKs.

MEKs may be bound to user credentials, which the host must provide to the drive in order for the associated data to be readable. A given MEK may be bound to one or more credentials. This model is captured in the TCG Opal [specification](https://trustedcomputinggroup.org/resource/storage-work-group-storage-security-subsystem-class-opal/).

MEKs, or other keys from which MEKs are derived, may be injected into the drive and tagged with address range metadata, such that subsequent I/Os which target that address range will be encrypted to that injected MEK. This model is captured in the TCG Key Per I/O (KPIO) [specification](https://trustedcomputinggroup.org/resource/tcg-storage-security-subsystem-class-ssc-key-per-i-o/).

MEKs may be securely erased, to effectively erase all data which was encrypted to the MEK. To erase an MEK, it is sufficient for the controller to erase the MEK itself or a key from which it was derived.

In an SED that takes Caliptra with OCP L.O.C.K. features enabled, Caliptra will act as a Key Management Block (KMB). The KMB will be the only entity that can read MEKs and program them into the SED's cryptographic engine. The KMB will expose services to controller firmware which will allow the controller to transparently manage each MEK's lifecycle, without being able to access the raw MEK itself.

# Threat model

The protected asset is the user data stored at rest on the drive. The adversary profile extends up to nation-states in terms of capabilities.

Adversary capabilities include:

- Interception of a storage device in the supply chain.
- Theft of a storage device from a data center.
- Destructively inspecting a stolen device.
- Running arbitrary firmware on a stolen device.
  - This includes attacks where vendor firmware signing keys have been compromised.
- Attempting to glitch execution of code running on general-purpose cores.
- Stealing debug core dumps or UART/serial logs from a device while it is operating in a data center, and later stealing the device.
- Gaining access to any class secrets, global secrets, or symmetric secrets shared between the device and an external entity.
- Executing code within a virtual machine on a multi-tenant host offered by the cloud service provider which manages an attached storage device.
- Accessing all device design documents, code, and RTL.

Given the above adversary profile, the following are a list of vulnerabilities that L.O.C.K. is designed to mitigate.

- Keys managed by storage controller firmware are compromised due to implementation bugs or side channels.
- Keys erased by storage controller firmware are recoverable via invasive techniques.
- MEKs are not fully bound to user credentials due to implementation bugs.
- MEKs are bound to user credentials which are compromised by a vulnerable host.
- Cryptographic erasure was not performed properly due to a buggy host.

# Architecture

The following figure shows the basic high-level blocks of OCP L.O.C.K.

*<p style="text-align: center;">Figure 1: OCP L.O.C.K high level blocks</p>*

<p align="center">
  <img src="./images/architecture_diagram.jpg" alt="Architecture Diagram" />
</p>

Caliptra that includes the optional OCP L.O.C.K. has a Key Management Block (KMB) that is the only entity that can derive the MEKs which protect user data and load the MEKs into the Key Cache of the Encryption Engine. The KMB derives MEKs using the following keys:

- A controller-supplied data encryption key (DEK). The DEK is the mechanism by which the controller enforces privilege separation between user credentials under TCG Opal, as well as the mechanism used to model injected MEKs under KPIO.

- A KMB-managed fuse epoch key (FEK), derived from secrets held in device fuses that are only accessible by the KMB. The FEK may be rotated a small number of times, providing assurance that an advanced adversary cannot recover key material used by the drive prior to the FEK rotation. KMB does not allow MEKs to be derived while the FEK is erased. KMB can report whether the FEK is erased and therefore whether the drive is clean.

- A controller epoch key (CEK), provided by the controller firmware when deriving each MEK. The controller firmware is responsible for managing and rotating this key. CEK rotation is a destructive operation.

- Zero or more partial MEKs (PMEKs), each of which is a cryptographically-strong value, encrypted to an externally-supplied access key. PMEKs enable multi-party authorization flows: the access key for each PMEK used to derive an MEK must be provided to the drive before the MEK can be used. Access keys are protected in transit using asymmetric encryption. This enables use-cases where the access key is served to the drive from a remote entity, without having to trust the host to which the drive is attached.

The DEK, FEK, and CEK do not require any changes to the host APIs for TCG Opal or KPIO.

Additional host APIs (i.e., Remote Key Management Services) are required to fully model FEK and CEK rotation, PMEKs, and injectable host entropy. Such APIs are beyond the scope of the present document.

MEKs are never visible to any firmware. To load an MEK into the Key Cache of the Encryption Engine, storage controller firmware interfaces to the Key Management Block to generate or retrieve a previously generated MEK and then cause hardware to load the MEK into the Encryption Engine. Each MEK has associated vendor-defined metadata, to identify for example the namespace and LBA range to be encrypted by the MEK.

Each PMEK is encrypted as rest using an externally-injected access key where that access key is not stored persistently on the storage device. If there is more than one PMEK used to generate an MEK, then it requires multiple authorities to unlock a given range of user data. Access keys may be held at rest in a remote key management service.

Each MEK is bound for its lifetime to the FEK and CEK, the list of PMEKs, and the DEK. To generate an MEK, the access key for each PMEK must be provided. All MEKs are removed from the Encryption Engine on a power cycle or during sanitization on the storage device. 

The DEK may be derived from or decrypted by a user's C_PIN to support legacy Opal. The DEK may be the imported key associated with a Key Per I/O key tag.
KMB generates [HPKE](https://datatracker.ietf.org/doc/rfc9180/) keypairs and stores them in internal volatile memory using a KEM algorithm such as ECDH or ML-KEM/Kyber. KMB can issue endorsements of KEM public keys allowing a Remote Key Management Services to ensure they only release access keys to authentic devices. PMEK access keys are encrypted in transit using these KEM keypairs. Upon drive reset, the access key must be re-encrypted to a new KEM for its associated PMEK to be usable.

KMB can maintain multiple active KEM keypairs. Nominally, one for each supported algorithm. KMB will automatically initialize a KEM for each supported algorithm and this may be done lazily. KMB will allow the controller to trigger KEM rotation. This can be done as part of zeroization.

KMB supports PMEK access key rotation where the storage controller must replace an old encrypted PMEK with a new encrypted PMEK. The end user must prove to KMB that they control both old and new access key. This is done by encrypting the new access key with the old access key. The new access key is therefore double-encrypted when provided to KMB with the old access key and with an ephemeral transport encryption key.

KMB is able to generate two kinds of keys: KEMs (used for access key transport encryption) and PMEKs (used for MEK derivation). A host is able to inject external entropy into KMB where it is held in internal volatile memory. Subsequent keys are randomly generated using both KMB's TRNG and the host's entropy as shown in figure 2.

*<p style="text-align: center;">Figure 2: KEM and PMEK Key Generation</p>*

<p align="center">
  <img src="./images/KEM_diagram.jpg" alt="KEM Diagram" />
</p>

## Interfaces

OCP L.O.C.K. provides two interfaces:

- The Encryption Engine interface is exposed from the vendor-implemented Encryption Engine to KMB, and defines a standard mechanism for programming MEKs and control messages.
- The mailbox interface is exposed from KMB to storage controller firmware, and enables the controller to manage MEKs.

## MEK derivation

<p align="center">
  <img src="./images/mek_derivation.svg" alt="MEK derivation" />
</p>

When controller firmware wishes to program an MEK to the Encryption Engine, the controller firmware performs the following steps:

1. Provides zero or more unlocked PMEKs to the KMB.
  - KMB initializes the MEK seed buffer with the FEK and then extends that MEK seed buffer using each given unlocked PMEK.
2. Provide a CEK and DEK to the KMB.
  - KMB derives the MEK using the given CEK, DEK, and the contents of the MEK seed buffer.
3. Provide MEK metadata to KMB, such as the MEK's associated namespace and logical block address range.
  - KMB programs the derived MEK and its metadata to the Encryption Engine.

### Sequence to mix a PMEK into the MEK seed

<p align="center">
  <img src="./diagrams/include_pmek.svg" alt="PMEK mixing" />
</p>

### Sequence to load an MEK

<p align="center">
  <img src="./diagrams/load_mek.svg" alt="MEK loading" />
</p>

### Sequence to load MEK into the Encryption Engine Key Cache

<p align="center">
  <img src="./diagrams/load_mek_into_ee.svg" alt="Loading MEK into EE" />
</p>

### Sequence to unload an MEK from the Encryption Engine Key Cache

<p align="center">
  <img src="./diagrams/unload_mek.svg" alt="Unloading MEK" />
</p>

### Sequence to unload all MEKs (i.e., purge) from the Encryption Engine Key Cache

<p align="center">
  <img src="./diagrams/clear_key_cache.svg" alt="Unloading all MEKs" />
</p>

### Legacy MEK derivation for TCG Opal

The controller is allowed to maintain a DEK that represents a given user's media encryption key. That DEK can be encrypted at rest by the user's C\_PIN.

When deriving the user's MEK, the controller can pass zero PMEKs in step 2, and the user's decrypted DEK in step 3.

### Legacy MEK derivation for Key Per I/O

MEKs injected with Key Per I/O will be considered as DEKs under OCP L.O.C.K.

When deriving the associated MEK, the controller can pass zero PMEKs in step 2, and the injected DEK in step 3.

## PMEK lifecycle

### PMEK generation

Controller firmware may request that KMB generate a random PMEK, bound to a given access key. KMB performs the following steps:

1. Unwrap the given PMEK access key. See [below](#transport-encryption-for-pmek-access-keys) for details on access key transport security.
2. Randomly generate a PMEK.
3. Derive a PMEK encryption key from the FEK and the decrypted access key.
4. Encrypt the PMEK to the PMEK encryption key.
5. Return the encrypted PMEK to the controller firmware.

Controller firmware may then store the encrypted PMEK in persistent storage.

**Sequence to generate a PMEK:**

<p align="center">
  <img src="./diagrams/generate_pmek.svg" alt="Generating a PMEK" />
</p>

### PMEK unlock

Encrypted PMEKs stored at rest in persistent storage are considered "locked", and must be unlocked before they can be used to derive MEKs. Unlocked PMEKs are also encrypted when handled by controller firmware. Unlocked PMEKs do not survive across device reset.

To unlock a PMEK, KMB performs the following steps:

1. Unwrap the given PMEK access key.
2. Derive the PMEK decryption key from the FEK and the decrypted access key.
3. Decrypt the PMEK using the PMEK decryption key.
4. Encrypt the PMEK using an ephemeral export key that is randomly initialized on startup and lost on reset.
5. Return the re-encrypted "unlocked" PMEK to the controller firmware.

Controller firmware may then stash the encrypted unlocked PMEK in volatile storage, and later provide it to the KMB when deriving an MEK, as described [above](#mek-derivation).

**Sequence to unlock a PMEK:**

<p align="center">
  <img src="./diagrams/unlock_pmek.svg" alt="Unlocking a PMEK" />
</p>

### PMEK access key rotation

The access key to which a PMEK is bound may be rotated. The user must prove that they have knowledge of both the old and new access key before a rotation is allowed. KMB performs the following steps:

1. Unwrap the given old and new access keys.
2. Derive the old PMEK decryption key from the FEK and the decrypted old access key.
3. Derive the new PMEK decryption key from the FEK and the decrypted new access key.
4. Decrypt the PMEK using the old PMEK decryption key.
5. Encrypt the PMEK using the new PMEK decryption key.
6. Return the re-encrypted PMEK to the controller firmware.

Controller firmware then erases the old encrypted PMEK and stores the new encrypted PMEK in persistent storage.

**Sequence to rotate the access key of a PMEK:**

<p align="center">
  <img src="./diagrams/rewrap_pmek.svg" alt="Rewrapping a PMEK" />
</p>

### Transport encryption for PMEK access keys

In OCP L.O.C.K., the KMB maintains a set of key-encapsulation-mechanism (KEM) keypairs, one per algorithm that OCP L.O.C.K. supports. Each KEM public key is endorsed with a certificate that is generated by Caliptra and signed by Caliptra's DICE identity. KEM keypairs are randomly generated on KMB startup, may be periodically rotated, and are lost when the drive resets.

When a user wishes to unlock a PMEK (which is required prior to deriving any MEKs bound to that PMEK), the user performs the following steps:

1. Obtain the KEM public key and certificate from the storage device.
2. Validate the KEM certificate and attached DICE certificate chain.
3. Run `Encaps` and encrypt their access key to the resulting shared key.
4. Transmit the KEM ciphertext and encrypted access key to the storage device.

Upon receipt, KMB will perform the following steps:

1. Run `Decaps` and decrypt the user's access key with the resulting shared secret.
2. Derive the PMEK encryption key using the FEK and the decrypted access key.
3. Perform PMEK generation, unlock, or rotation actions detailed [above](#pmek-lifecycle).

Upon drive reset, the KEMs are regenerated, and any access keys for PMEKs that had been unlocked prior to the reset will need to be re-provisioned.

**Sequence to endorse an encapsulation public key:**

<p align="center">
  <img src="./diagrams/endorse_encapsulation_pub_key.svg" alt="Endorseing a KEM Pub key" />
</p>

### Access key rotation flows

As noted [above](#pmek-access-key-rotation), during access key rotation the user must prove knowledge of both the old and new access keys. This is accomplished using a slight variation on the encaps-decaps flow. When a new access key is provided to KMB during a rotation, the new access key is double-encrypted: first to the old access key, and then to the shared secret obtained from the `Encaps` operation.

The KMB then performs a double decryption when unwrapping the new access key, proving that the provisioner of the new access key also knows the old access key.

**Sequence to rotate an encapsulation key:**

<p align="center">
  <img src="./diagrams/rotate_encapsulation_key.svg" alt="Rotateing a KEM Encapsulation Key" />
</p>

### Algorithm support

OCP L.O.C.K. supports the following KEM algorithms:

- P384 ECDH
- Hybridized ML-KEM-1024 with P-384 ECDH

**Sequence to obtain the supported algorithms:**

<p align="center">
  <img src="./diagrams/get_algorithms.svg" alt="Get Supported Algorithms" />
</p>

## Status function

OCP L.O.C.K. has the following function to assist with determining the status.

**Sequence to obtain the current status of OCP L.O.C.K.:**

<p align="center">
  <img src="./diagrams/get_status.svg" alt="Get Status" />
</p>

# Hardware

The following figure describes the OCP L.O.C.K. hardware.

Figure 8: KMB block diagram

This figure will be fleshed out with additional details as they become available.

## Memory requirements

This section will be fleshed out with additional details as they become available.

## Cryptography requirements

This section will be fleshed out with additional details as they become available.

## KMB-Encryption Engine interface

This section defines the interface between the Key Management Block (KMB) and an Encryption Engine. An Encryption Engine is used to encrypt/decrypt user data and its design and implementation are vendor specific. Media Encryption Keys (MEKs) are the keys which are generated within KMB and used by Encryption Engine to encrypt and decrypt user data. This interface is used to load MEKs from KMB to Encryption Engine or to cause the Encryption Engine to unload (i.e., remove) loaded MEKs. The MEKs transferred between the KMB and the Encryption Engine shall not be accessible by the controller firmware.

### Overview

The Encryption Engine uses a stored MEK to encrypt and decrypt user data. For the purposes of this specification, the entity within the Encryption Engine used to store the MEKs is called Key Cache. Each encryption and description of user data is coupled to a specific MEK which is stored in Key Cache bound to a unique identifier, called metadata. Each (metadata, MEK) pair is also associated with additional information, called aux, which is used neither as MEK nor an identifier, but has some additional information about the pair. Therefore, the Key Cache as an entity which stores (metadata, aux, MEK) tuples.

In order to achieve the security goals for KMB, KMB is limited to be the unique component which loads an (metadata, aux, MEK) tuple into the Key Cache and unloads a tuple within the device, so that MEKs can only be exposed to KMB and Encryption Engine. Controller firmware arbitrates all operations in the KMB to Encryption Engine interface, therefore controller firmware is responsible for managing which MEK is loaded in Key Cache. Controller firmware has full control on metadata and optional aux. Figure 9 is an illustration of the KMB to Encryption Engine interface that shows:

-    the tuple for loading an MEK;
-    the Metadata for unloading an MEK; and 
-    an example of a Key Cache within the Encryption Engine.

*<p style="text-align: center;">Figure 9: KMB to Encryption SFR Interface</p>*

<p align="center">
  <img src="./images/kmb_ee.svg" alt="Encryption Engine diagram" />
</p>

KMB uses Special Function Registers (SFRs) to communicate with Encryption Engine which are described in the following sections.

### Special Function Registers (SFRs)

KMB uses Special Function Registers (SFRs) to communicate with Encryption Engine as shown in Table 1 and each of the following subsections describe the registers.

*<p style="text-align: center;">Table 1: KBM to Encryption Engine SFRs</p>*

| Register                   | Address        | Byte Size | Description |
| :------------------------- | :------------- | :-------- | :---------- |
| Control                    | SFR_BASE + 0h  | 4h        | Register to handle commands |
| Metadata                   | SFR_BASE + 10h | 14h       | Register to provide metadata |
| Auxiliary Data (AUX)       | SFR_BASE + 30h | 20h       | Register to provide auxiliary values |
| Media Encryption Key (MEK) | SFR_BASE + 50h | 40h       | Register to provide MEK |

SFR_BASE is an address that is configured on KMB. The integrator should make sure that KMB can access these SFRs through these addresses.

#### Control register

Figure 10 defines the Control register used to sequence the execution of a command and obtain the status of that command.

*<p style="text-align: center;">Figure 10: Offset SFR_Base + 0h: CTRL – Control</p>*

| Bits  | Type | Reset | Description |
| :---- | :--- | :---- | :---------- |
| 31    | RO   | 0h    | **Ready (RDY):** After an NVM Subsystem Reset, this bit is set to 1b, then the Encryption Engine is ready to execute commands. If this bit is set to 0b, then the Encryption Engine is not ready to execute commands. |
| 30:20 | RO   | 0h    | Reserved |
| 19:16 | RO   | 0h    | **Error (ERR):** If the DONE bit is set to 1b by the Encryption Engine, then this field is set to a non-zero value to indicate the Encryption Engine detected an error during the execution the command specified by the CMD field. The definition of a non-zero value is vendor specific. <table><tr><td><b>Value</b></td><td><b>Description</b></td></tr><tr><td>0h</td><td>Command Successful</td></tr><tr><td>1h to 3h</td><td>Reserved</td></tr><tr><td>4h to Fh</td><td>Vendor Specific</td></tr></table> If the DONE bit is set to 1b by the Encryption Engine and this field is set to 0h, then the Encryption Engine is indicating a successful execution of a command specified by the CMD field. If the DONE bit is set to 1b by KMB, then the field is set to 0000b. |
| 15:6  | RO   | 0h    | Reserved |
| 5:2   | RW   | 0h    | **Command (CMD):** This field specifies the command to execute or the command associated with the reported status. <table><tr><tr><b>Value</b></tr><tr><b>Description</b></tr></tr><tr><td>0h</td><td>Reserved</td></tr><tr><td>1h</td><td><b>Load MEK:</b> Load the key specified by the AUX field and MEK register into the Encryption Engine as specified by the METD field.</td></tr><tr><td>2h</td><td><b>Unload MEK:</b> Unload the MEK from the Encryption Engine as specified by the METD field.</td></tr><tr><td>3h</td><td><b>Sanitize:</b> Unload all of the MEKs from the Encryption Engine (i.e., Sanitize the Encryption Engine MEKs).</td></tr><tr><td>4h to Fh</td><td>Reserved</td></tr></table> |
| 1     | RW   | 0b    | **Done (DN):** This bit indicates the completion of a command by the Encryption Engine. If this bit is set to 1b by the Encryption Engine, then the Encryption Engine has completed the command specified by the CMD field. If the EXE bit is set to 1b and this bit is set to 1b, then the Encryption Engine has completed executing the command specified by the CMD field and the ERR field indicates the status of the execution of that command. A write of the value 1b to this bit shall cause the Encryption Engine to:<ul><li>set this bit to 0b;</li><li>set the EXE bit to 0b; and</li><li>set the ERR field to 0000b.</li></ul> |
| 0     | RW   | 0b    | **Execute (EXE):** A write of the value 1b to this bit specifies that the Encryption Engine is to execute the command specified by the CMD field. If the DONE bit is set to 1 by KMB, then the bit is set to 0b. |

From the KMB, the Controller register is the register to write a command and receive its execution result. From its counterpart, the Encryption Engine, the Controller register is used to receive a command and write its execution result.

The expected change flow of the Controller register to handle a command is as follows:

1. If **RDY** is set to 1b, then KMB writes **CMD** and **EXE**
    1. **CMD:** either 1h, 2h or 3h
    2. **EXE:** 1b
2. The Encryption Engine writes** **ERR** and **DN**
    1. **ERR:** either 0b or a non-zero value depending on the execution result
    2. **DN:** 1b
3. The KMB writes **DN**
    1. **DN:** 1b
4. The Encryption Engine writes **CMD**, **ERR**, **DN** and **EXE**
    1. **CMD:** 0h
    2. **ERR:** 0h
    3. **DN:** 0b
    4. **EXE:** 0b

The KMB therefore interacts with the Control register as follows in the normal circumstance:

1. The KMB writes **CMD** and **EXE**
    1. **CMD:** either 1h, 2h or 3h
    2. **EXE:** 1b
2. The KMB waits **DN** to be 1
3. The KMB writes **DN**
    1. **DN:** 1b
4. The KMB waits **DN** to be 0

Since the Controller register is in fact a part of the Encryption Engine whose implementation can be unique by each vendor, behaviors of the Control register with the unexpected flow are left for vendors. For example, a vendor who wants robustness might integrate a write-lock into the Control register in order to prevent two almost simultaneous writes on EXE bit.

#### Metadata Register

Figure 11 defines the Metadata register.

*<p style="text-align: center;">Figure 11: Offset SFR_Base + 10h: METD – Metadata</p>*

| Bytes | Type  | Reset | Description |
| :---- | :---- | :---- | :---------- |
| 19:00 | RW    | 0h    | **Metadata (METD):** This field specifies metadata that is vendor specific and specifies the entry in the Encryption Engine for the Encryption Key.|

For the security goal of this project, the KMB and the Encryption Engine must be the only components which have access to MEKs. Each MEK must then be bound to a unique identifier, which can be accessible by other components, in order for an appropriate key to be used for any key-related operations including data I/O. In a LOCK-enabled system, the **METD** field is expected to be used as such identifier.

Instead of generating a random and unique identifier within the KMB while generating an MEK, the KMB takes an **METD** value as input from the controller firmware and write to the Metadata register without any modification for the sake of the following reasons:

1. A vendor does not need to implement an additional algorithm to map between identifiers in its own system and in the KMB
2. A vendor-unique key-retrieval algorithm can easily be leveraged into a **METD**-generation algorithm

In order to reduce ambiguity, two examples of the **METD** field will be given: Logical Block Addressing (LBA) range-based metadata; and key-tag based metadata.

When an SSD stores data with address-based encryption, an MEK can be uniquely identified by a (LBA range, Namespace ID) pair. Then, the (LBA range, Namespace ID) pair can be leveraged into METD as on Figure 12.

*<p style="text-align: center;">Figure 12: LBA Range Based Metadata Format</p>*

<p align="center">
  <img src="./images/lba_nsid_info.jpg" alt="LBA and NSID" />
</p>

Address-based encryption is not however the only encryption mechanism in SSDs. For example, in TCG Key Per I/O, an MEK is selected by a key tag, which does not map to an address. Figure 13 shows an example of **METD** in such cases.

*<p style="text-align: center;">Figure 13: Key Tag Based Metadata Format</p>*

<p align="center">
  <img src="./images/key_tag_info.jpg" alt="Key Tag Info" />
</p>

The above examples are not the only possible values of **METD**. Vendors are encouraged to design and use their own **METD** if it fits better to their system.

#### Auxiliary Data Register

Figure 14 defines the Auxiliary Data register.

*<p style="text-align: center;">Figure 14: Offset SFR_Base + 20h: AUX – Auxiliary Data</p>*

| Bytes | Type | Reset | Description |
| :---- | :--- | :---- | :---------- |
| 31:00 | RW   |  0h   | **Auxiliary Data (AUX):** This field specifies auxiliary data associated to the MEK. |

At first glance, the usage of **AUX** might not be straightforward. The intuition behind introducing the **AUX** field is to support vendor-specific features on MEKs. The KMB itself is only supporting fundamental functionalities in order to minimize attack surfaces on MEKs. Moreover, vendors are not restricted to design and implement their own MEK-related functionalities on the Encryption Engine unless they can be used to exfiltrate MEKs. In order to support these functionalities, some data may be associated and stored with an MEK and the **AUX** field is introduced to store such data with each MEK.

When the controller firmware instructs the KMB to generate a new MEK, the controller firmware is expected to provide an **AUX** value. Similar to the **METD** field, the KMB will write the **AUX** value into the Auxiliary Data register without any modification.

One simple use case of the **AUX** field is to store an offset of initialization vector or nonce. It can also be used in a more complicated use case. Here is an example. Suppose that there exists a vendor who wants to design a system which supports several modes of operation through the Encryption Engine while using the KMB. Then, a structure of **AUX** value as on Figure 15 can be used.

*<p style="text-align: center;">Figure 15: Auxiliary Data Format Example</p>*

<p align="center">
  <img src="./images/aux_info.jpg" alt="Aux Info" />
</p>

When the controller firmware instructs KMB to generate an KMB, the controller firmware can use the **AUX** value to specify which mode of operation should be used and which value should be used as an initialization vector or a nonce with the generated MEK.

#### Media Encryption Key (MEK) register

Figure 16 defines the MEK register.

*<p style="text-align: center;">Figure 16: Offset SFR_Base + 40h: MEK – Media Encryption Key</p>*

| Bytes | Type | Reset | Description |
| :---- | :--- | :---- | :---------- |
| 31:00 |  WO  |   0h  | **Secret Encryption Key (SEK):** This field specifies a 256-bit Encryption Key |
| 63:32 |  WO  |   0h  | **Tweakable Key (TWK):** This is the 256-bit AES-XTS tweakable key. |

Since the AES-XTS is one of the most popular algorithms for data encryption, the MEK register is also designed with the key format of AES-XTS. The layout of the MEK register is however designed to help understanding the structure. The Encryption Engine is not restricted to only support the AES-XTS. The choice of encryption algorithm is solely dependent on vendors. When a vendor decides to use a different encryption algorithm, an MEK can be seen as a 64-byte random value rather than a (secret key, tweak key) pair and how to slice the 64-byte random value into an encryption key will be left to the vendor.

As a part of Caliptra, KMB protects MEKs as securely as any secret key in Caliptra. Within Caliptra, MEKs are only ever present in the Key Vault, so that they can be protected against any firmware-level attacks. When KMB needs to write an MEK into the MEK register, it will be accomplished by using the DMA engine. Given an index and a destination identifier, the DMA engine copies the key value stored in the key vault of given index to the destination address to which the DMA engine translates the destination identifier. 

### KMB command sequence

Figure 17 shows a sample command execution. This is an expected sequence when the controller firmware instructs the KMB to generate a new MEK. The internal behavior of the Encryption Engine is one of several possible mechanisms, and it can be different per vendor.

*<p style="text-align: center;">Figure 17: Command Execution Example</p>*

<p align="center">
  <img src="./images/cmd_exe_example.jpg" alt="Command Execution Example" />
</p>

## FEK fuse requirements

A storage device equipped with OCP L.O.C.K. will be equipped with N 256-bit ratchet-secret fuse banks, dubbed R<sub>0</sub>..R<sub>N-1</sub>. 4 ≤ N ≤ 16. These ratchet secrets have the following requirements:

- Each ratchet secret can individually transition from all-zeroes → randomized → all-ones. R<sub>X</sub> is only randomized once R<sub>X-1</sub> has transitioned to all-ones.
- Programmable via the Caliptra fuse controller.
- Only readable by Caliptra Core, via fuse registers.
    - Internally, the fuse registers will be treated like the DICE UDS, in that their contents can only be deposited into Key Vault slots, without direct visibility by Caliptra firmware.
-Caliptra Core firmware can detect which ratchet secrets are all-zeroes, randomized, or all-ones. This can be done by representing a counter in fuses, which maps to ratchet secret states. Controller firmware would be responsible for ensuring that the counter value corresponds with the ratchet secrets' current state.<br>The counter values map to the following states:

| State  | Description |
| :----- | :---------- |
| 4<sub>i</sub> + 0 | R<sub>i</sub> has begun being programmed with randomness, but is not yet considered randomized. |
| 4<sub>i</sub> + 1 | R<sub>i</sub> has been randomized. |
| 4<sub>i</sub> + 2 | R<sub>i</sub> has begun being programmed to all-ones, and is no longer considered randomized. |
| 4<sub>i</sub> + 3 | R<sub>i</sub> has been programmed to all-ones. |

This scheme allows ratchet state transitions to be resilient in the face of unexpected power loss. A power loss during randomization will burn the ratchet being randomized.

The counter is readable by Caliptra Core firmware and controller firmware.

### Lifecycle transitions

Caliptra features a Stable Identity secret, which is a non-ratchetable secret derived from the DICE UDS, the current value of the field entropy fuse bank, as well as the current lifecycle and debug states. The Stable Identity secret can be used to protect long-lived data.

The FEK is derived from Caliptra's Stable Identity secret, along with the currently-active ratchet-secret fuse bank. In normal cases, if the currently-active ratchet-secret fuse bank is unprogrammed or erased, the FEK is disabled and no MEKs are allowed to be derived or programmed. There are two edge cases, where the FEK is derived solely from Caliptra's Stable Identity secret:

- When the device is fresh from the factory and no ratchet-secret fuse banks have been programmed.
- When the device has programmed all of its ratchet-secret fuse banks, and the owner has opted into an operating mode where data written to the storage device can no longer be erased via fuse ratchet.

The device will go through the following state transitions over its lifespan:

1. At the factory, R<sub>0</sub>..R<sub>N-1</sub> are all-zero.
    1. Caliptra derives the FEK from Caliptra's Stable Identity secret.
    2. Caliptra allows MEKs to be programmed to the storage encryption engine, derived from the FEK.
    3. Caliptra firmware reports a bit indicating that it is operating in a state where any data written cannot be ratchet-erased.
2. The storage controller programs R<sub>0</sub> with randomness.
    1. Caliptra detects that R<sub>0</sub> is randomized, and derives the FEK from R<sub>0</sub> and Caliptra's Stable Identity secret.
    2. Caliptra allows MEKs to be programmed to the storage encryption engine, derived from the FEK.
3. The storage controller programs R<sub>0</sub> to all-ones and resets.
    1. Upon next reset, Caliptra detects that there are no randomized ratchet secrets and does not derive an FEK.
    2. Caliptra does not allow any MEKs to be programmed to the storage encryption engine.
4. The storage controller programs R<sub>1</sub> to a random value and resets.
    1. Upon next reset, Caliptra detects that R<sub>1</sub> is randomized, and derives the FEK from R<sub>1</sub> and Caliptra's Stable Identity secret.
    2. Caliptra allows MEKs to be programmed to the storage encryption engine, derived from the FEK.
5. The storage controller programs R<sub>1</sub> to all-ones and resets.
6. The storage controller programs R<sub>2</sub> to a random value and resets.
7. The storage controller programs R<sub>2</sub> to all-ones and resets.
8. The storage controller programs R<sub>3</sub> to a random value and resets.
    1. See steps 2 and 3 for Caliptra's behavior in each state.
    
   ...

9. The storage controller programs R<sub>N-1</sub> to all-ones and resets.
    1. Upon next reset, Caliptra detects that there are no randomized ratchet secrets, and no all-zeroes ratchet secrets.
    2. Caliptra derives the FEK from Caliptra's Stable Identity secret.
    3. Caliptra allows MEKs to be programmed to the storage encryption engine, derived from the FEK.
    4. Caliptra firmware reports a bit indicating that it is operating in a perma-dirty state, where no future ratchets are possible.

### FEK fuse programming

OCP L.O.C.K contains a fuse block that contains the ability to program N number of FEKs, one at a time. A device out of manufacturing does not program an FEK and the device behaves as existing devices do today where the SSD firmware manages the key. This is known as the EMPTY state. OCP L.O.C.K supports a PROGAM_NEXT_FEK API to then program the initial FEK. That FEK is then used to derive all MEKs. That FEK can be erased by using the ERASE_CURRENT_FEK Api. Once that FEK is erased, no FEK exists in OCP L.O.C.K. and no MEKs can be generated by OCP L.O.C.K until the PROGAM_NEXT_FEK API causes a new FEK to be programmed.

Once all of the N FEKs have been programmed and erased, no FEK exists in OCP L.O.C.K. and no MEKs can be generated by OCP L.O.C.K. The ENABLE_PERMANENT_FEK API can be used to permanently allow the device to behave as existing devices do today where the SSD firmware manages the key.

There can be errors programming or erasing an FEK. If these errors occur, the APIs can be use to retry the operation. If there still is an error, then the device is in an unusable state.

The diagram below has an example flow where the number of FEKs available to be programmed is 4 (N=4):

| State transition                               | active_slot | slot_state           | next_action          |
| :--------------------------------------------- | :---------: | :------------------: | :------------------- |
| Factory                                        | 0           | EMPTY                | PROGRAM_NEXT_FEK     |
| Program first entry                            | 0           | PROGRAMMED           | ERASE_CURRENT_FEK    |
| Erase first entry                              | 0           | ERASED               | PROGRAM_NEXT_FEK     |
| Program second entry                           | 1           | PROGRAMMED           | ERASE_CURRENT_FEK    |
| Erase second entry<br>(recoverable failure)    | 1           | PARTIALLY_ERASED     | ERASE_CURRENT_FEK    |
| Erase second entry                             | 1           | ERASED               | PROGRAM_NEXT_FEK     |
| Program third entry<br>(recoverable failure)   | 2           | PARTIALLY_PROGRAMMED | PROGRAM_NEXT_FEK     |
| Program third entry<br>(unrecoverable failure) | 2           | PARTIALLY_PROGRAMMED | ERASE_CURRENT_FEK    |
| Erase failed entry                             | 2           | ERASED               | PROGRAM_NEXT_FEK     |
| Program fourth entry                           | 3           | PROGRAMMED           | ERASE_CURRENT_FEK    |
| Erase fourth entry                             | 3           | ERASED               | ENABLE_PERMANENT_FEK |
| Enable perma dirty                             | 3           | NON_FUSE_RATCHETABLE | NONE                 |

## Error reporting and handling

This section describes OCP L.O.C.K error reporting and handling.

This section will be fleshed out with additional details as they become available.

### Fatal errors

This section will be fleshed out with additional details as they become available.

### Non-fatal errors

This section will be fleshed out with additional details as they become available.

# Runtime firmware environment

This section provides an extension to the runtime firmware environment defined for OCP Caliptra runtime firmware specification due to the support of OCP L.O.C.K.

## Boot and initialization

This section defines additional boot and initialization flows needed to support OCP L.O.C.K.

The Runtime Firmware main function SHALL cause the generation of the FEK and store this into the Key Vault. The FEK is generated from the FEK fuses.

The following sections define the additional Caliptra mailbox commands due to supporting OCP L.O.C.K.

## GET_STATUS

Exposes a command that allows the SoC to determine if the Encryption Engine is ready to process commands as well vendor-defined drive crypto engine status data. 

Command Code: 0x4753_5441 (“GSTA”)

Table: GET_STATUS input arguments

| Name  | Type  | Description |
| :---- | :---- | :---------- |
|chksum | u32   | Checksum over other input arguments, computed by the caller. Little endian. |

Table: GET_STATUS output arguments

| Name         | Type    | Description |
| :----------- | :------ | :---------- |
| chksum       | u32     | Checksum over other output arguments, computed by Caliptra. Little endian. |
| fips_status  | u32     | Indicates if the command is FIPS approved or an error |
| engine_ready | u32     | Ready status of the storage device crypto engine.<br>OCP L.O.C.K. defines low range, vendor defines high range. <ul><li>Byte 0 Bit 0: 1 = Ready 0 = Not ready</li></ul> | Reserved |
| reserved     | u32[4]  | 

## GET_ALGORITHMS

Exposes a command that allows the SoC to determine the types of algorithms supported by KBM for endorsement, KEM, PMEK, and access key generation. 

Command Code: 0x4743_4150 (“GCAP”)

Table: GET_ALGORITHMS input arguments

| Name     | Type    | Description |
| :------- | :------ | :---------- |
| chksum   | u32     | Checksum over other input arguments, computed by the caller. Little endian. |

Table: GET_ALGORITHMS output arguments

| Name                   | Type   | Description |
| :--------------------- | :----- | :---------- |
| chksum                 | u32    | Checksum over other output arguments, computed by Caliptra. Little endian. |
| fips_status            | u32    | Indicates if the command is FIPS approved or an error |
| endorsement_algorithms | u32    | Identifies the supported endorsement algorithms:<ul><li>Byte 0 bit 0: ecdsa_secp384r1_sha384[^4]</li><li>Byte 0 bit 1: ml-dsa-87[^5]</li></ul> |
| hpke_algorithms        | u32    | Identifies the supported HPKE algorithms:<ul><li>Byte 0 bit 0: kem_id = 0x0011, aead_id = 0x0002, kdf_id = 0x0002[^6]</li><li>Byte 0 bit 1: bit 1: kem_id = 0x0a25, aead_id = 0x0002, kdf_id = 0x0002[^7]</li></ul> |
| pmek_algorithms        | u32    | Indicates the size of PMEKs:<ul><li>Byte 0 bit 0: 256 bits</li></ul> |
| access_key_algorithm   | u32    | Indicates the size of access keys:<ul><li>Byte 0 bit 0: 256 bits, with a 128-bit truncated SHA384 ID</li></ul> |
| reserved               | u32[4] | Reserved |

## CLEAR_KEY_CACHE

This command unloads all MEKs in the Encryption Engine and deletes all keys in KMB.

Command Code: 0x4353_4543 (“CSEC”)?????

Table: CLEAR_KEY_CACHE input arguments

| Name        | Type | Description |
| :---------- | :--- | :---------- |
| chksum      | u32  | Checksum over other input arguments, computed by the caller. Little endian. |
| rdy_timeout | u32  | Timeout in ms for encryption engine to become ready for a new command |
| cmd_timeout | u32  | Timeout in ms for command to crypto engine to complete |

Table: CLEAR_KEY_CACHE output arguments

| Name        | Type    | Description |
| :---------- | :------ | :---------- |
| chksum      | u32     | Checksum over other output arguments, computed by Caliptra. Little endian. |
| fips_status | u32     | Indicates if the command is FIPS approved or an error |

## ENDORSE_ENCAPSULATION_PUB_KEY

This command generates a signed certificate for the specified KEM using the specified endorsement algorithm.

Command Code: 0x4E45_505B (“EEPK”)

Table: ENDORSE_ENCAPSULATION_PUB_KEY input arguments

| Name                  | Type   | Description |
| :-------------------- | :----- | :---------- |
| chksum                | u32    | Checksum over other input arguments, computed by the caller. Little endian |
| kem_handle            | u32    | Handle for KEM keypair held in KMB memory|
| endorsement_algorithm | u32    | Endorsement algorithm identifier. If 0h, then return public key |

Table: ENDORSE_ENCAPSULATION_PUB_KEY output arguments

| Name            | Type      | Description |
| :-------------- | :-------- | :---------- |
| chksum          | u32       | Checksum over other output arguments, computed by Caliptra. Little endian |
| fips_status     | u32       | Indicates if the command is FIPS approved or an error |
| pub_key         | KemPubKey | KEM public key |
| endorsement_len | u32       | Length of endorsement data (N) |
| endorsement     | u8[N]     | DER-encoded X.509 certificate (includes nonce as extension) |

## ROTATE_ENCAPSULATION_KEY

This command rotates the KEM keypair indicated by the specified handle and stores the new KEM keypair in volatile memory within KMB.

Command Code: 0x5245_4E4B (“RENK”)

Table: ROTATE_ENCAPSULATION_KEY input arguments

| Name       | Type | Description |
| :--------- | :--- | :---------- |
| chksum     | u32  | Checksum over other input arguments, computed by the caller. Little endian. |
| kem_handle | u32  | Handle for old KEM keypair held in KMB memory. |

Table: ROTATE_ENCAPSULATION_KEY output arguments

| Name       | Type | Description |
| :--------- | :--- | :---------- |
| chksum     | u32  | Checksum over other output arguments, computed by Caliptra. Little endian |
| fips_status| u32  | Indicates if the command is FIPS approved or an error |
| kem_handle | u32  | Handle for new KEM keypair held in KMB memory |

## GENERATE_PMEK

This command unwraps the specified access key, generates a random PMEK, then uses the FEK and access key to encrypt the PMEK which is returned for the Storage Controller to persistently store.

Command Code: 0x5245_4E4B (“RENK”)

Table: GENERATE_PMEK input arguments

| Name               | Type             | Description |
| :----------------- | :--------------- | :---------- |
| chksum             | u32              | Checksum over other input arguments, computed by the caller. Little endian. |
| pmek_algorithm     | u32              | Indicates the size of PMEKs. Only one bit shall be reported: <ul><li>Byte 0 bit 0: 256 bits</li></ul> |
| wrapped_access_key | WrappedAccessKey | KEM-wrapped access key: <ul><li>access_key_algorithm</li><li>kem_handle</li><li>kem_algorithm</li><li>kem_ciphertext</li><li>encrypted_access_key</li></ul> |

Table: GENERATE_PMEK output arguments

| Name               | Type          | Description |
| :----------------- | :------------ | :---------- |
| chksum             | u32           | Checksum over other output arguments, computed by Caliptra. Little endian. |
| fips_status        | u32           | Indicates if the command is FIPS approved or an error |
| new_encrypted_pmek | EncryptedPmek | PMEK encrypted to access_key_2 |

## REWRAP_PMEK

This command Unwraps access_key_1 and enc_access_key_2. Then access_key_1 is used to decrypt enc_access_key_2. The specified PMEK is decrypted using KDF(FEK, "PMEK", access_key_1). A new PMEK is encrypted with the output of KDF(FEK, "PMEK", access_key_2). The new encrypted PMEK is returned.

The Storage Controller stores the returned new encrypted PMEK. The Storage Controller may attempt to do a decryption the new PMEK without an error before deleting old PMEK. Controller firmware erases the old encrypted PMEK.

Command Code: 0x5245_5750 (“REWP”)

Table: REWRAP_PMEK input arguments

| Name                     | Type                   | Description |
| :----------------------- | :--------------------- | :---------- |
| chksum                   | u32                    | Checksum over other input arguments, computed by the caller. Little endian. |
| wrapped_access_key_1     | WrappedAccessKey       | KEM-wrapped access key: <ul><li>access_key_algorithm</li><li>kem_handle</li><li>kem_algorithm</li><li>kem_ciphertext</li><li>encrypted_access_key</li></ul> |
| wrapped_enc_access_key_2 | DoubleWrappedAccessKey | KEM-wrapped (access_key_2 encrypted to access_key_1) |

Table: REWRAP_PMEK output arguments

| Name               | Type          | Description |
| :----------------- | :------------ | :---------- |
| chksum             | u32           | Checksum over other output arguments, computed by Caliptra. Little endian. |
| fips_status        | u32           | Indicates if the command is FIPS approved or an error |
| new_encrypted_pmek | EncryptedPmek | PMEK encrypted to access_key_2 |

## UNLOCK_PMEK

This command Unwraps wrapped_access_key. Then the unwrapped access_key is used to decrypt locked_pmek using KDF(FEK, "PMEK", access_key). An "unlocked" PMEK is encrypted with the the ephemeral export secret. The encrypted unlocked PMEK is returned.

Command Code: 0x554E_4C50 (“UNLP”)

Table: UNLOCK_PMEK input arguments

| Name               | Type             | Description |
| :----------------- | :--------------- | :---------- |
| chksum             | u32              | Checksum over other input arguments, computed by the caller. Little endian. |
| wrapped_access_key | WrappedAccessKey | KEM-wrapped access key: <ul><li>access_key_algorithm</li><li>kem_handle</li><li>kem_algorithm</li><li>kem_ciphertext</li><li>encrypted_access_key</li></ul> |
| locked_pmek        | EncryptedPmek    | PMEK encrypted to the FEK and access key. |

Table: UNLOCK_PMEK output arguments

| Name          | Type          | Description |
| :------------ | :------------ | :---------- |
| chksum        | u32           | Checksum over other output arguments, computed by Caliptra. Little endian. |
| fips_status   | u32           | Indicates if the command is FIPS approved or an error |
| unlocked_pmek | EncryptedPmek | PMEK encrypted to an export secret that is rotated  on reset |

## MIX_PMEK

This command initializes the MEK seed if not already initialized, decrypts the specified PMEK with the with the ephemeral export secret, and then updates the MEK seed in KMB by performing a KDF with the MEK seed, the decrypted PMEK, and the string PMEK mix”.

When generating an MEK, one or more MIX_PMEK commands are processed to modify the MEK seed.

Command Code: 0x4D50_4D4B (“MPMK”)

Table: MIX_PMEK input arguments

| Name          | Type          | Description |
| :------------ | :------------ | :---------- |
| chksum        | u32           | Checksum over other input arguments, computed by the caller. Little endian. |
| unlocked_pmek | EncryptedPmek | PMEK encrypted to an export secret that is rotated  on reset |

Table: MIX_PMEK output arguments

| Name         | Type | Description |
| :----------- | :--- | :---------- |
| chksum       | u32  | Checksum over other output arguments, computed by Caliptra. Little endian. |
| fips_status  | u32  | Indicates if the command is FIPS approved or an error |

## LOAD_MEK

This command causes the specified controller data encryption key to be combined with the MEK seed. The final MEK seed, specified metadata, and aux_metadata are loaded into the Encryption Engine Key Cache. The metadata is specific to the storage controller and specifies the information to the Encryption Engine on where within the Key Cache, the MEK is loaded.

The storage controller specified data encryption key may be a C_PIN-derived secret for Opal or a per-MEK value in KPIO.

The final MEK is generated by performing a KDF on the existing MEK seed in the KMB, the CEK, the DEK, and the string “MEK”.

When generating an MEK, the MEK seed is initialized if no PMEK has already been mixed into the MEK seed.

Command Code: 0x4C4D_454B (“LMEK”)

Table: LOAD_MEK input arguments

| Name         | Type   | Description |
| :----------- | :----- | :---------- |
| chksum       | u32    | Checksum over other input arguments, computed by the caller. Little endian. |
| metadata     | u8[20] | Metadata for MEK to load into the drive crypto engine (i.e. NSID + LBA range) |
| aux_metadata | u8[32] | Auxiliary metadata for the MEK (optional; i.e. operation mode) |
| cek          | u8[32] | "Controller epoch key". May be rotated by the controller as part of a cryptographic purge. |
| dek          | u8[32] | "Data encryption key". May be a C_PIN-derived secret in Opal or a per-MEK value in KPIO. |
| rdy_timeout  | u32    | Timeout in ms for encryption engine to become ready for a new command |
| cmd_timeout  | u32    | Timeout in ms for command to crypto engine to complete |

Table: LOAD_MEK output arguments

| Name         | Type | Description |
| :----------- | :--- | :---------- |
| chksum       | u32  | Checksum over other output arguments, computed by Caliptra. Little endian. |
| fips_status  | u32  | Indicates if the command is FIPS approved or an error |

## UNLOAD_MEK

This command causes the MEK associated to the specified metadata to be unloaded for the Key Cache of the Encryption Engine. The metadata is specific to the storage controller and specifies the information to the Encryption Engine on where within the Key Cache, the MEK is loaded.

Command Code: 0x554D_454B (“UMEK”)

Table: UNLOAD_MEK input arguments

| Name         | Type    | Description |
| :----------- | :------ | :---------- |
| chksum       | u32     | Checksum over other input arguments, computed by the caller. Little endian. |
| metadata     | u8[20]  | Metadata for MEK to unload from the drive crypto engine (i.e. NSID + LBA range) |
| rdy_timeout  | u32     | Timeout in ms for encryption engine to become ready for a new command |
| cmd_timeout  | u32     | Timeout in ms for command to crypto engine to complete |

Table: UNLOAD_MEK output arguments

| Name         | Type   | Description |
| :----------- | :----- | :---------- |
| chksum       | u32    | Checksum over other output arguments, computed by Caliptra. Little endian |
| fips_status  | u32    | Indicates if the command is FIPS approved or an error |

## ENUMERATE_KEM_HANDLES

This command returns a list of all currently-active KEM handles for resources held by KMB.

Command Code: 0x4548_444C (“EHDL”)

Table: ENUMERATE_KEM_HANDLES input arguments

| Name   | Type | Description |
| :----- | :--- | :---------- |
| chksum | u32  | Checksum over other input arguments, computed by the caller. Little endian. |

Table: ENUMERATE_KEM_HANDLES output arguments

| Name             | Type         | Description |
| :--------------- | :----------- | :---------- |
| chksum           | u32          | Checksum over other output arguments, computed by Caliptra. Little endian. |
| fips_status      | u32          | Indicates if the command is FIPS approved or an error |
| kem_handle_count | u32          | Number of KEM handles (N) |
| kem_handles      | KemHandle[N] | List of (KEM handle value, KEM algorithm) tuples |

## ERASE_CURRENT_FEK

This command programs all un-programmed bits in the current FEK slot, so all bits are programmed. May resume a previously-failed erase operation.

Command Code: 0x4543_464B (“ECFK”)

Table: ERASE_CURRENT_FEK input arguments

| Name   | Type | Description |
| :----- | :--- | :---------- |
| chksum | u32  | Checksum over other input arguments, computed by the caller. Little endian. |

Table: ERASE_CURRENT_FEK output arguments

| Name        | Type | Description |
| :---------- | :--- | :---------- |
| chksum      | u32  | Checksum over other output arguments, computed by Caliptra. Little endian. |
| fips_status | u32  | Indicates if the command is FIPS approved or an error |

## PROGRAM_NEXT_FEK

This command generates a random key and programs it into the next-available FEK slot.

Command Code: 504E_464B (“PNFK”)

Table: PROGRAM_NEXT_FEK input arguments

| Name   | Type | Description |
| :----- | :--- | :---------- |
| chksum | u32  | Checksum over other input arguments, computed by the caller. Little endian. |

Table: PROGRAM_NEXT_FEK output arguments

| Name        | Type | Description |
| :---------- | :--- | :---------- |
| chksum      | u32  | Checksum over other output arguments, computed by Caliptra. Little endian. |
| fips_status | u32  | Indicates if the command is FIPS approved or an error |

## ENABLE_PERMANENT_FEK

This command enables a perma-dirty state where the FEK is derived from non-ratchetable secrets. Will only take effect once all FEK fuse slots are programmed and erased.

Command Code: 4550_464B (“EPFK”)

Table: ENABLE_PERMANENT_FEK input arguments

| Name   | Type | Description |
| :----- | :--- | :---------- |
| chksum | u32  | Checksum over other input arguments, computed by the caller. Little endian. |

Table: ENABLE_PERMANENT_FEK output arguments

| Name        | Type | Description |
| :---------- | :--- | :---------- |
| chksum      | u32  | Checksum over other output arguments, computed by Caliptra. Little endian. |
| fips_status | u32  | Indicates if the command is FIPS approved or an error |

## REPORT_EPOCH_KEY_STATE

This command reports the state of the epoch keys. The controller indicates the state of the CEK, while Caliptra senses the internal state of the FEK.

Command Code: 5245_4B53 (“REKS”)

Table: REPORT_ROOT_KEY_STATE input arguments

| Name      | Type   | Description |
| :-------- | :----- | :---------- |
| chksum    | u32    | Checksum over other input arguments, computed by the caller. Little endian. |
| cek_state | u16    | CEK state:<table><tr><td><b>Value</b></td><td><b>Description</b></td></tr><tr><td>0h</td><td>ERASED</td></tr><tr><td>1h</td><td>PROGRAMMED</td></tr><tr><td>2h to FFFFh</td><td>Reserved</td></tr></table> |
| nonce     | u8[16] | Freshness nonce |


Table: REPORT_ROOT_KEY_STATE output arguments

| Name            | Type        | Description |
| :-------------- | :---------- | :---------- |
| chksum          | u32         | Checksum over other output arguments, computed by Caliptra. Little endian. |
| fips_status     | u32         | Indicates if the command is FIPS approved or an error |
| total_fek_slots | u16         | Total number of FEK slots |
| active_fek_slot | u16         | Currently-active FEK slot |
| fek_slot_state  | u16         | State of the currently-active FEK slot:<table><tr><td><b>Value</b></td><td><b>Description</b></td></tr><tr><td>0h</td><td>EMPTY (Able to load MEKs)</td></tr><tr><td>1h</td><td>PARTIALLY_PROGRAMMED (Not to load MEKs)</td></tr><tr><td>2h</td><td>PROGRAMMED (Able to load MEKs)</td></tr><tr><td>3h</td><td>PARTIALLY_ERASED (Not to load MEKs)</td></tr><tr><td>4h</td><td>ERASED (Not to load MEKs)</td></tr><tr><td>5h</td><td>NON_FUSE_RATCHETABLE (Able to load MEKs)</td></tr><tr><td>6h to FFFFh</td><td>Reserved</td></tr></table> |
| next_fek_action | u16         | Next action that can be taken on the active slot:<table><tr><td><b>Value</b></td><td><b>Description</b></td></tr><tr><td>0h</td><td>NONE</td></tr><tr><td>1h</td><td>PROGRAM</td></tr><tr><td>2h</td><td>ERASE</td></tr><tr><td>3h</td><td>ENABLE_IO_WITHOUT_RATCHET</td></tr><tr><td>4h to FFFFh</td><td>Reserved</td></tr></table> |
| eat_len         | u16         | Total length of the IETF EAT |
| eat             | u8[eat_len] | CBOR-encoded and signed IETF EAT |

## Fault handling

A mailbox command can fail to complete in the following ways due to OCP L.O.C.K.:

-    An ill-formed command
-    Encryption Engine timeout
-    Encryption Engine reported error

In all of these cases, the error is reported in the command returned status.

Depending on the type of fault, the SoC may to resubmit the mailbox command.

Each mailbox command that causes a command to execute on the Encryption Engine includes a timeout value is specified by the command. Caliptra aborts the command executing on the Encryption Engine if the Encryption Engine does not complete the command within the specified timeout and reports a LOCK_ENGINE_TIMEOUT result code.

Table 3 defines the additional Caliptra result codes due to supporting OCP L.O.C.K.

*<p style="text-align: center;">Table 3: OCP L.O.C.K. mailbox command result codes</p>*

Table 2: OCP L.O.C.K. mailbox command result codes

| Name                   |      Value               |   Description |
| :--------------------- | :----------------------- | :------------ |
| LOCK_ENGINE_TIMEOUT    | 0x4C45_544F<br>(“LETO”)  | Timeout occurred when communicating with the drive crypto engine to execute a command | 
| LOCK_ENGINE_CODE + u16 | 0x4443_xxxx<br>(“ECxx”)  | Vendor-specific error code in the low 16 bits |
| LOCK_BAD_ALGORITHM     | 0x4C42_414C<br>(“LBAL”)  | Unsupported algorithm, or algorithm does not match the given handle |
| LOCK_BAD_HANDLE        | 0x4C42_4841<br>(“LBHA”)  | Unknown handle |
| LOCK_NO_HANDLES        | 0x 4C4E_4841<br>(“LNHA”) | Too many extant handles exist |
| LOCK_KEM_DECAPSULATION | 0x4C4B_4445<br>(“LKDE”)  | Error during KEM decapsulation |
| LOCK_ACCESS_KEY_UNWRAP | 0x4C41_4B55<br>(“LAKU”)  | Error during access key decryption |
| LOCK_PMEK_DECRYPT      | 0x4C50_4445<br>(“LPDE”)  | Error during PMEK decryption |

# Terminology

The following acronyms and abbreviations are used throughout this document.

| Abbreviation | Description |
| :----------- | :---------- |
| AES          | Advanced Encryption Standard |
| CSP          | Cloud Service Provider |
| CEK          | Controller Epoch Key |
| DEK          | Data Encryption Key |
| DICE         | Device Identifier Composition Engine |
| DRBG         | Deterministic Random Bit Generator |
| ECDH         | Elliptic-curve Diffie–Hellman |
| ECDSA        | Elliptic Curve Digital Signature Algorithm |
| FEK          | Fuse Epoch Key |
| HMAC         | Hash-Based Message Authentication Code |
| KDF          | Key Derivation Function |
| KEM          | Key Encapsulation Mechanism |
| KMB          | Key Management Block |
| L.O.C.K.     | Layered Open-Source Cryptographic Key-management |
| MEK          | Media Encryption Key |
| ML-KEM       | Module-Lattice-Based Key-Encapsulation Mechanism |
| NIST         | National Institute of Standards and Technology |
| OCP          | Open Compute Project |
| PMEK         | Partial Media Encryption Key |
| RTL          | Register Transfer Level |
| SED          | Self-encrypting drive |
| SSD          | Solid-state drive |
| UART         | Universal asynchronous receiver-transmitter |
| XTS          | XEX-based tweaked-codebook mode with ciphertext stealing |

# Acknowledgements

The Caliptra Workgroup acknowledges the following individuals for their contributions to this specification:

Currently this list is identical to the list contributors.

 
# References
1. <a id="ref-1"></a>[Self-encrypting deception: weaknesses in the encryption of solid state drives](https://www.cs.ru.nl/~cmeijer/publications/Self_Encrypting_Deception_Weaknesses_in_the_Encryption_of_Solid_State_Drives.pdf) by Carlo Meijer and Bernard van Gastel
2. <a id="ref-2"></a>[TCG Opal](https://trustedcomputinggroup.org/resource/storage-work-group-storage-security-subsystem-class-opal/)
3. <a id="ref-3"></a>[TCG Key Per I/O](https://trustedcomputinggroup.org/resource/tcg-storage-security-subsystem-class-ssc-key-per-i-o/)
4. <a id="ref-4"></a>[RFC 8446: The Transport Layer Security (TLS) Protocol Version 1.3](https://datatracker.ietf.org/doc/html/rfc8446)
5. <a id="ref-5"></a>[Internet X.509 Public Key Infrastructure: Algorithm Identifiers for ML-DSA](https://datatracker.ietf.org/doc/draft-ietf-lamps-dilithium-certificates/)
6. <a id="ref-6"></a>[RFC 9180: Hybrid Public Key Encryption](https://www.rfc-editor.org/rfc/rfc9180.html)
7. <a id="ref-7"></a>[Hybrid PQ/T Key Encapsulation Mechanisms](https://datatracker.ietf.org/doc/draft-irtf-cfrg-hybrid-kems/) 
