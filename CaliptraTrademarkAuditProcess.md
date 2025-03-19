

**Caliptra Trademark Audit Process**

**Version 0.2**

**Document history**

| Version | Date | Changes |
| :---- | :---- | :---- |
| 0.1 | 2024/09/30 | First draft of the report |
| 0.2 | 2025/01/21 | Additional Changes after Feedback |

# Table of Contents
- [Introduction](#introduction)
- [Caliptra Trademark Auditing Process](#caliptra-trademark-auditing-process)
  - [Suggestion](#suggestion)
  - [Roles](#roles)
  - [Properties of the Scheme](#properties-of-the-scheme)
  - [Overview of the Example Scheme](#overview-of-example-scheme)
  - [Specific Questions for the Scheme Rules](#specific-questions-for-the-scheme-rules)
  - [Typical Process for Obtaining the Caliptra Trademark](#typical-process-for-obtaining-the-caliptra-trademark)

# Introduction

The objective of the Caliptra Trademark Auditing Process is to provide guidelines to Caliptra instantiation, with focus on the most important security aspects and properties for “real-world” security, based on the security objectives and use cases of Caliptra. It is expected that the Caliptra Trademark Auditing Process will be less detailed than the NIST certification requirements and the auditing process and documents should focus on analyzing vendor architecture and implementation of Caliptra on vendor products, rather than testing of vendor products. 

This document defines an auditing process to be used by vendors to determine if the vendor’s products meet the Caliptra trademark requirements. The auditing process will be captured in a “Process” document that can be used by vendors to request permission to use the Caliptra trademark. Additionally, a “Checklist” document will be provided, which can be used by vendors to determine if the vendor is complying with the Caliptra Integration Specification. 

The main objective of the [Checklist and evaluation methodology document](https://ghttps://github.com/chipsalliance/Caliptra/blob/main/CaliptraChecklistAndEvaluationMethodology.md) is to ensure the secure integration of Caliptra in another device, to ensure that Caliptra can leverage its main security functionality (security services) and remain secure. The main security functionality of Caliptra as a silicon RoT, when integrated, is to:

* Cryptographically measure its own **code** & **configuration**   
* Sign these measurements with a unique **attestation key**   
* Provide an interface for storing additional measurements
* **Report measurements** to a host and/or external entity, which can further verify the authenticity & integrity of the device (a.k.a Attestation)  
* Furthermore, Caliptra offers **DICE hardware identity service**.

# Caliptra Trademark Auditing Process

The checklist describes the specific requirements to be reviewed by a 3rd party laboratory. 

The Caliptra Trademark Auditing Process defines the roles and process that third-party laboratories use to achieve the approval of the Trademark Usage.

The following contains suggestions on how the scheme can be defined.

## Suggestion

* Start with a minimal scheme and develop and grow when there is a need and as maturity grows.  
* Add more specifics when identified and needed.  
* Make sure feedback about the scheme is possible to incorporate to facilitate growth and improvements.

## Roles

* **Manufacturer:** Manufacturer of device that claims Caliptra integration.  
* **Laboratory:** OCP SAFE 3rd party laboratory for evaluation of TOE, for potential recommendation of approval of Caliptra Trademark Usage.  The laboratory should have experience reviewing RTL.  
* **Caliptra Trademark Owner (TAC):** Approves or disapproves Caliptra Trademark Usage based on evaluation and recommendation by Laboratory.  
* **OCP SAFE Certification body:** Acts independently, and it´s accreditation for Laboratories is used.

## Properties of the Scheme

* The scheme for the Caliptra Trademark Auditing Process is not under the OCP SAFE scheme.  
* The scheme for the Caliptra Trademark Auditing Process relies directly on laboratories that are approved under OCP SAFE Level 2\.  
  * Comment: This creates a dependence of the Caliptra Trademark Audit Scheme to the OCP SAFE maintenance.  
* The scope of the evaluation by the laboratory is in short limited to  
  * The physical and logical scope to establish correct integration of Caliptra IP, which includes the creation of a Caliptra wrapper and secure implementation of the SoC RoT to send measurements. The exact physical and logical scope is also affected by the checklist and the evaluation methodology.  
  * The scope in terms of fulfilling security properties is given by the checklist and the evaluation methodology.  
* The objective of the effort to pass the Caliptra Trademark Auditing Process is expected to be limited for both laboratory, manufacturer and TAC. This is determined by the checklist, the evaluation methodology and additionally the practical interpretation of the scheme by TAC and the laboratories.  
* The scope of the manufacturer in short is to  
  * Provide checklist self-assessment and sufficient evidence for laboratory to assess fulfillment of checklist according to the evaluation methodology. This is expected to include provisioning of RTL, SoC ROM/FW showing completion of the integration by the manufacturer.  
* The scope of the laboratory in short is to  
  * Verify the self-assessment of the checklist and additional information provided by the manufacturer using the evaluation methodology.

## Overview of Example Scheme

For a formal certification scheme there are rules and documents of the scheme that defines it. In this example scheme definition, the discussed possible solution for the Caliptra Trademark Audit Process is commented within parenthesis.

* Conformity Assessment Bodies (Entities)  
  * Certification Body (CB).   
    *(In this case the Caliptra TAC)*  
  * Laboratories.   
    *(In this case from OCP SAFE level 2 laboratories)*  
* Related to Certification Body   
  (In this case using and dependence to OCP SAFE)  
  * Application to become Caliptra Trademark Laboratory   
    *(In this case using and dependence to OCP SAFE)*  
    * Criteria for Caliptra Trademark Laboratory  
      * E.g. National accreditation needed, ISO 17025\. Note: ISO 17025 requires Evaluation Methodology of scheme to accredit laboratory, in general.  
    * Technical capabilities for Caliptra  
    * Terms and conditions  
  * Audit process for Caliptra Trademark Laboratory (Technical capabilities)  
    *(In this case using and dependence to OCP SAFE)*  
  * Renewal of accepted Caliptra Trademark Laboratory  
    *(In this case using and dependence to OCP SAFE)*  
  * Publication of accepted Caliptra Trademark Laboratory  
    *(In this case using and dependence to OCP SAFE)*  
  * Audit protocols  
    *(In this case using and dependence to OCP SAFE)*  
* Related to Products and Caliptra Trademark Usage  
  * Application for Caliptra Trademark Usage for a TOE  
    *(Task for Caliptra TAC to develop.)*  
  * Publication of all approved products for Caliptra Trademark usage  
    *(Task for Caliptra TAC to develop.)*  
  * Process specification for obtaining Caliptra Trademark  
    *(A brief suggestion is outlined in this document)*  
  * Rules for Caliptra Trademark Usage  
    *(Task for Caliptra TAC to develop. See suggestions for some aspects in this document.)*  
* Related to Evaluation  
  * Evaluation methodology (audit process) (to be used by Laboratory or Vendor)  
    *(Scope of current work)*  
    * Checklist  
    * How to apply checklist (Evaluation methodology)  
  * *Evaluation Technical Report Template*  
    *(Task for Caliptra TAC to develop or to delegate to the laboratories)*  
  * *Communication between Laboratory and Manufacturer*  
    *(Task for Caliptra TAC to develop or to delegate to the laboratories)*  
  * *Communication between Laboratory and Caliptra Trademark Owner*  
    *(Task for Caliptra TAC to develop.)*  
  * *A forum where the Labs can ask questions and make sure the level of evaluation is more or less consistent across labs. In such a forum the scheme can be further developed and improved.*  
    *(Task for Caliptra TAC to develop.)*

## Specific Questions for the Scheme Rules

This section considers some specific questions and suggestions for discussion on how this could be handled.

* Updates and changed versions of device that integrates Caliptra  
  * Updates of the software or hardware of the device that integrates Caliptra that are judged by the manufacturer to **not affect the security** of the Caliptra integration.  
    * **Suggestion:** Updates that are considered for the **same product** do not affect the Caliptra Trademark usage for the device.  
      **Rationale:** Caliptra Trademark Audit Process is a low-effort scheme, updates are encouraged and adding a new audit processes for each update of the device will not be feasible. On the other hand, when publishing the granted products, the version that was considered in the audit process can be clearly stated. Any updates are the responsibility of the manufacturer.  
    * **Suggestion:** Updates or changes that are considered large enough for a **new product** should be candidates for a new Caliptra Trademark Audit process and independently needs the TAC to consider to grand the Caliptra Trademark. Since the changes are judged not to change the security of the already audited Caliptra integration, a new Caliptra Trademark Audit process is not required. Instead, a motivation by the manufacturer to TAC of why the changes are not affecting the security of the Caliptra integration is required, before the TAC grants the Caliptra Trademark for the new product.  
      **Rationale:** Each product that is granted the Caliptra Trademark should be listed, and it is necessary that TAC has the power to control which products are granted the Caliptra Trademark. On the other hand, if the changes are small, TAC could consider this low-effort solution for handling deltas and changes. The typical product certification schemes require a full reevaluation for any updates. However, in some schemes, in practice, heave reuse of previous evaluations can be made.  
  * Updates of the hardware of the device that integrates Caliptra that are expected to **affect the security** of the Caliptra integration.  
    * **Suggestion:** A new Caliptra Trademark Audit Process is required. If the manufacturer is using the same laboratory as for a similar previous version, it is expected that the audit process is more efficient.  
* Validity of granted Caliptra Trademark  
  * Revocation of Caliptra Trademark Usage
    * **Suggestion:** Caliptra TAC can revoke the usage of the Caliptra Trademark under certain conditions.  
      * The validity time of the Caliptra Trademark Usage has expired.  
      * Critical vulnerabilities have been discovered in either the integration of Caliptra, or Caliptra, that would fail a new Caliptra Trademark audit, and the vulnerabilities have not, or cannot, be mitigated.  
      * New threats have emerged that were not considered in the Caliptra Trademark Process, and that critically effects the security.
  * **Suggestion:** There is validity time granted for each Caliptra Trademark usage.  
  * **Suggestion:** Caliptra 1.X will in time be replaced by Caliptra 2.X with PQC compliance. A date will be set for when the grant of using Caliptra trademark with Caliptra 1.X will no longer be given because it doesn't support PQC algorithms.  After that date, no other Calitpra 1.X trademarks will be given.

## Typical Process for Obtaining the Caliptra Trademark

1. The manufacturer contacts a licensed laboratory.  
2. The laboratory and manufacturer agree on terms and sign a contract to help respond to the documentation required within the checklist and methodology document.  
3. The laboratory and manufacturer communicate and jointly, when aligned, provide an application for Caliptra Trademark Usage for a TOE to Caliptra Trademark Owner TAC, signed by both laboratory and manufacturer.  
4. It is the manufacturer's responsibility to provide a self-assessment of why the checklist requirements are fulfilled, together with other necessary information for the laboratory.  
5. The laboratory evaluates and assesses the TOE using the provided filled-in checklist and the evaluation methodology. Iterations with the manufacturer are expected until all issues are resolved, as judged by the laboratory.  
6. The laboratory produces an evaluation technical report, using an evaluation technical report template, and sends this to the Caliptra Trademark Owner.  
7. The Caliptra Trademark Owner TAC assesses the submitted evaluation technical report, and, if needed, communicates with the laboratory for any questions and comments.  
8. The Caliptra Trademark Owner determines to grant or deny the usage of the Caliptra Trademark for the TOE.  
9. Caliptra Trademark Owner publishes the granted Caliptra Trademark Usage for the TOE, together with other previously accepted TOEs.