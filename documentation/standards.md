
# CSCI 265 Team Standards and Processes (Phase 2)

## Team name: YOUR TEAM NAME HERE

## Project/product name: YOUR PRODUCT NAME HERE

## Key contact person and email

 - NameA, their@emailaddy *main contact*

## Document structure

In this document we will be addressing three core areas of standards and processes:
 - Documentation standards and processes
 - Coding standards and processes
 - Version control standards and processes

Each section includes discussion of how those standards/processes will be enforced, and how they will be reviewed for potential updates if/as needed.

## Documentation standards and processes

Within the top level of the team project repository, Jeremy will maintain a 'Documentation' sub-directory with the following list of files that will contain contributions and work-product from all members of the team. The git lead, Amitoj, will add the skeleton documents to the 'Documentation' folder at the start of each project phase. Each file may be updated as the project progresses to record changes, clarifications, and decisions made at team meetings. When an update not included in the original submission is made, a note should be included with the update that shows the date the update occurred and the reason for the update (e.g. 2024-10-01: Updated to reflect decision at Team Meeting on Sep 25, 2024). We will use GitHub's history to track edits to documents. Therefore, changes that include removing text may be performed by the document's team members assigned below. For this reason, commit messages should be descriptive enough for the other team members and instructor to know why edits were made. All team members will be responsible for creating documents for their original submissions. The listed primary and secondary maintainers have been assigned based on their lead and understudy roles. Maintenance roles currently listed as "TBD" will be assigned before their document's submission to at least one team member, and this document will be updated.

- proposal.md (Patrick): The preliminary proposal deliverable (phase 1)
- charter.md (Jeremy): The team charter deliverable (phase 1)
- requirements.md (Yagna/Artem): The product requirements deliverable (phase 2)
- standards.md (Will/Jeremy): The standards and processes deliverable (phase 2)
- logicaldesign.md (Jeremy/Patrick): The logical design deliverable (phase 3)
- userguide.md (Artem/Amitoj): The user guide/manual deliverable (phase 3)
- technicaldesign.md (TBD): The physical/technical design deliverable (phase 4)
- proofconcept.md (TBD): The proof of concept deliverable (phase 4)
- testplan.md (TBD): The test plan deliverable (phase 5)
- closeout.md (TBD): The project closeout deliverable (phase 6)

An 'Images' subdirectory will be placed within the top project directory. Two subdirectories will be within the 'Images' subdirectory, namely Documentation and Test. The 'Documentation' directory will include all images to be included in our markdown files for submission. Images in this directory should be named based on the relevant document they are intended to be included within, followed by an underscore and a descriptor (e.g. "standards_figure1.png"). The 'Test' directory will include all images used as test input for coding and decoding images with payloads. A naming convention has yet to be chosen for these images, as encoding keys for the steganography portion of our product may be included in the filename. This document should be updated to reflect this decision as soon as possible.

Documents should follow the structure provided in the project phase specifications and the sample documents provided by Prof. Wessels. If an additional document section is required to convey an aspect of our team's project specific to our team, it should follow the same formatting standards to maintain continuity.

Each contributing team member should thoroughly check both spelling (Canadian English) and grammar before initiating a pull request to master. The team members assigned to a document's maintenance should perform a final check of the document before its submission.
Push and merge requests must be made on GitHub, and two team members must approve them before they can be pushed or merged to the master branch. At the team meeting following each phase's submission, Jeremy will ask the team how the documentation standards and processes are working for each team member so that additional assignments/reassignments can be made to document maintenance or changes can be made as needed.

## Coding standards and processes

Detail the coding standards and processes to be followed (can provide links to existing industry standards), how they will be enforced, and how they will be reviewed for updating if/as needed.

## Version control standards and processes

The git lead will enforce these standards along with everyone else holding each other accountable:

- No pushing directly to [`master`](https://github.com/csci265-team/project/tree/master). Create pull requests instead.
- Pull requests need to be created against [`master`](https://github.com/csci265-team/project/tree/master) to get code merged in.
- At least two team members need to approve changes in a PR before code can be merged into [`master`](https://github.com/csci265-team/project/tree/master).
- The creator of the pull request can not merge their own pull request.
- Force pushes should be avoided.

Teams have been made on GitHub for eaech of the roles in this project.
A project page on GitHub is created to keep track of tasks. This is to be used by everyone to keep each other accountable.

[^1]: 2024-10-01 - This footnote was added to provide an example footnote.
