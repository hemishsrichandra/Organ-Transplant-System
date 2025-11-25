# Organ-Transplant-System

A C-based console application designed to manage organ donors and
recipients efficiently using linked lists and file handling. This system
simulates a simplified organ-allocation workflow used in real transplant
coordination, incorporating blood compatibility rules, urgency-based
prioritization, and persistent storage.

## 📌 Overview

The **Organ Transplant System** allows a coordinator to:

-   Maintain lists of **recipients** waiting for Heart, Kidney, Liver,
    or Lung transplants.
-   Add new **donors**, automatically check compatibility, and allocate
    organs.
-   Prioritize **super urgent** cases.
-   Delete recipients who become ineligible.
-   Persist all records using text files.

The system internally uses **singly linked lists** for dynamic data
handling.

## 🔑 Features

### 1. Donor Entry & Automatic Allocation

-   Add a donor for any organ.
-   System checks:
    -   Blood group compatibility.
    -   Super-urgency recipients.
-   If a match is found:
    -   Displays allocation message.
    -   Removes recipient from the list.
-   If no match:
    -   Displays message indicating the organ expired.

### 2. Recipient Management

Add new recipients with: - Name\
- Blood group\
- Age\
- Date of entry\
- Hospital name\
- Super urgency (`YES` or `NO`)

Each recipient is stored in the linked list corresponding to their
required organ.

### 3. View Donor & Recipient Lists

View formatted lists for: - Heart donors/recipients\
- Kidney donors/recipients\
- Liver donors/recipients\
- Lungs donors/recipients

### 4. Delete Recipient

Remove a recipient by name if they: - Are no longer eligible\
- Pass away before allocation

## 🩸 Blood Group Compatibility

A dedicated function implements actual blood-donation rules,
including: - `O-` as universal donor\
- `AB+` as universal recipient\
- Rh factor logic\
- All A/B/O/AB matching rules

## 🧠 Allocation Logic

When a donor is added:

1.  Scan recipient list for **super-urgent** compatible patients.
2.  If none, match with the first compatible recipient.
3.  Delete the matched recipient from the list.
4.  Add donor to the donor list if allocation succeeds.
5.  If no match found → organ expires.

## 🖥️ Menu Options

  Option   Function
  -------- ----------------------------------------
  **1**    Enter new donor and attempt allocation
  **2**    Add new recipient
  **3**    View donor list
  **4**    View recipient list
  **5**    Delete a recipient
  **6**    Save all data and exit

## ⚙️ How to Compile & Run

### Compile

gcc organ_system.c -o organ_system

### Run

./organ_system


Ensure all `.txt` files are present in the same directory; if not, the
program will create them.

## 📂 File Format

### Recipient File Format

    name,bloodGroup,age,entryDate,hospital,superUrgency

Example:

    Rahul,O+,35,12-05-2024,Apollo,YES

### Donor File Format

    name,bloodGroup,age,dateOfDeath

## 🛠️ Technologies Used

-   C Programming Language\
-   Linked Lists\
-   File Handling\
-   String Processing\
-   Memory Management

## Project done by:  
Y.Hemish Sri Chandra  
Lalith Sai Redroutu  
Praneeth Kumar Dola  
