Organ Transplant System
=======================

- A C-based console application designed to manage organ donors and recipients with efficient allocation logic, realistic blood-compatibility rules, urgency prioritization, and persistent data storage. The system uses linked lists for dynamic memory handling and text files for long-term record maintenance.


Overview
--------

The Organ Transplant System allows transplant coordinators to:

- Maintain recipient lists for Heart, Kidney, Liver and Lungs.
- Add donors and automatically allocate organs based on compatibility.
- Prioritize super-urgent cases.
- Remove ineligible or deceased recipients.
- Save and load all data through text files.


Features
--------

1. Donor Entry and Automatic Allocation
- Add donors for any supported organ.
- The system checks:
- - Blood group compatibility
- - Super-urgent recipients first
- If matched:
- - Displays allocation details
- - Removes the recipient from the list
- If unmatched:
- - The organ is marked as expired

2. Recipient Management
Each recipient entry includes:
- Name  
- Blood group  
- Age  
- Date of entry  
- Hospital name  
- Super-urgency status (YES / NO)

Separate linked lists are maintained for each organ.

3. List Viewing
View structured donor and recipient lists for:
- Heart  
- Kidney  
- Liver  
- Lungs  

4. Delete Recipient
Remove a recipient by name if:
- They become medically ineligible  
- They pass away before allocation  

5. Blood Group Compatibility
Implements realistic transfusion-based compatibility rules:
- Universal donor handling  
- Universal recipient handling  
- Rh factor rules  
- ABO group matching  

6. Allocation Logic
When a donor is added:
1. Search for compatible super-urgent recipients.  
2. If none, match the first compatible recipient in the list.  
3. Remove the matched recipient.  
4. Add the donor to the donor list.  
5. If no match exists, the organ expires.  


Menu Options

| Option | Description                              |
|--------|------------------------------------------|
|   1    | Enter a new donor and attempt allocation |
|   2    | Add a new recipient                      |
|   3    | View donors list                         |
|   4    | View recipients list                     |
|   5    | Delete a recipient                       |
|   6    | Save all data and exit                   |



Compilation and Execution

Compile
- bash
- - gcc organ_system.c -o organ_system

Run
- bash
- - ./organ_system


All required `.txt` files should be stored in the same directory.  
If missing, the program automatically creates them.


File Formats
------------

Recipient File Format

- name,bloodGroup,age,entryDate,hospital,superUrgency

- Example:
- - Rahul,O+,35,12-05-2024,Apollo,YES


Donor File Format

- name,bloodGroup,age,dateOfDeath


Technologies Used
-----------------

- C Programming  
- Linked Lists  
- File Handling  
- Dynamic Memory Management  
- String Processing  


Contributors
------------
- Y. Hemish Sri Chandra  
- Lalith Sai Redroutu  
- Dola Praneeth Kumar Gunda
