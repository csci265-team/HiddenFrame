
# CSCI 265 Team Standards and Processes (Phase 2)

## Team name: Project HiddenFrame

## Project/product name: HiddenFrame

## Key contact person and email

 - Artem Trefilov, artlov59@gmail.com *main contact*

## Document structure

In this document, we will be addressing three core areas of standards and processes:
 - Documentation standards and processes
 - Coding standards and processes
 - Version control standards and processes

Each section includes a discussion of how those standards/processes will be enforced and how they will be reviewed for potential updates if/as needed.

## Documentation standards and processes

Within the top level of the team project repository, Jeremy will maintain a [`/documentation`](../documentation) sub-directory with the following list of files that will contain contributions and work-product from all members of the team. Jeremy will add the skeleton documents to the 'Documentation' folder at the start of each project phase. Each file may be updated as the project progresses to record changes, clarifications, and decisions made at team meetings. When an update not included in the original submission is made, a note should be included with the update that shows the date the update occurred and the reason for the update (e.g. 2024-10-01: Updated to reflect decision at Team Meeting on Sep 25, 2024). We will use GitHub's history to track edits to documents. Therefore, changes that include removing text may be performed by the document's team members assigned below. For this reason, commit messages should be descriptive enough for the other team members and instructor to know why edits were made. All team members will be responsible for creating documents for their original submissions. The listed primary and secondary maintainers have been assigned based on their lead and understudy roles. Maintenance roles currently listed as "TBD" will be assigned before their document's submission to at least one team member, and this document will be updated.

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

A [`/resources/images`](../resources/images) subdirectory will be placed within the top project directory. Two subdirectories will be within the [`/resources/images`](../resources/images) subdirectory, namely Documentation and Test. The [`/resources/images/documentation`](../resources/images/documentation) directory will include all images to be included in our markdown files for submission. Images in this directory should be named based on the relevant document they are intended to be included within, followed by an underscore and a descriptor (e.g. "standards_figure1.png"). The [`/resources/images/test`](../resources/images/test) directory will include all images used as test input for coding and decoding images with payloads. A naming convention has yet to be chosen for these images, as encoding keys for the steganography portion of our product may be included in the filename. This document should be updated to reflect this decision as soon as possible.

Documents should follow the structure provided in the project phase specifications and the sample documents provided by Prof. Wessels. If an additional document section is required to convey an aspect of our team's project specific to our team, it should follow the same formatting standards to maintain continuity.

Each contributing team member should thoroughly check both spelling (Canadian English) and grammar before initiating a pull request to master. The team members assigned to a document's maintenance should perform a final check of the document before its submission. Pull and merge requests must be made on GitHub, and two team members must approve them before they can be pushed or merged to the master branch. At the team meeting following each phase's submission, Jeremy will ask the team how the documentation standards and processes are working for each team member so that additional assignments/reassignments can be made to document maintenance or changes can be made as needed.

## Coding standards and processes

The coding standards we intend to follow are the CSCI 265 project standards supplied by our professor, Dave Wessels. 
They will be enforced and reviewed by the code review team. Pull requests will not be merged unless these standards are followed.
More details on the coding standards can be found at: http://csci.viu.ca/~wesselsd/courses/csci265/standards.html

## Version control standards and processes

The git lead will enforce these standards along with everyone else, holding each other accountable:

#### Rules for all branches/PRs

These are general rules that should be applied to all branches and pull requests:

- Force pushes should be avoided.
- The creator of the pull request can not merge their own pull request.
- If a review requesting changes is created on a PR, then the PR cannot be merged until the reviewer approves the PR.
- Once all the requirements are met anyone on the team can merge PRs except the creator of said PR.

#### Adding to staging

Our project has a [`staging`](https://github.com/csci265-team/project/tree/staging) branch. This branch will have latest working code
This is the branch that everyone pulls from and then gets merged into master at the end of each phase thus, our goal is to keep this branch stable and protected.
Below are some of the explicit rules protecting this branch:

- No pushing directly to [`staging`](https://github.com/csci265-team/project/tree/staging). Create pull requests instead.
- Pull requests need to be created against [`staging`](https://github.com/csci265-team/project/tree/staging) to get code merged in.
- At least two team members need to approve changes in a PR before code can be merged into [`staging`](https://github.com/csci265-team/project/tree/staging).


#### Adding to master

Our project has a [`master`](https://github.com/csci265-team/project/tree/master) branch. This branch will be the one submitted to the professor.
This is the branch that gets submitted at the end of each phase, and thus, our goal is to keep this branch stable and protected.
Below are some of the explicit rules protecting this branch:

- No pushing directly to [`master`](https://github.com/csci265-team/project/tree/master). Create pull requests from staging instead.
- Pull requests need to be created against [`master`](https://github.com/csci265-team/project/tree/master) to get code merged in.
- Git Lead will create the pull request against master from staging at the end of each phase.
- At least two team members need to approve changes in a PR before code can be merged into [`master`](https://github.com/csci265-team/project/tree/master).

#### Adding to dev branches

Our project also has "dev" branches (`*-dev`), which will follow the naming convention `nameOfMemeber-dev`.
Each team member can make a branch with this naming scheme, and the following rules will apply to it:

- Only the owner of a branch can push directly to it.
- If someone other than the owner wants to make changes to this type of branch, they must make a pull request against it. (`nameOfMemeber-dev` <--- `xyz-branch`)
- The pull request may only be merged after approval from the owner of said branch

#### Other branches

Team members may create any number of branches other than the ones mentioned above.
These branches should follow the same standards as the ["dev" branch standards](#adding-to-dev-branches) unless the creator explicitly communicates otherwise.
Some naming recommendations are given below:
- `feat-*` For branches where any number of team members are working on a certain feature


Teams have been made on GitHub for each role in this project.
A project page on GitHub is created to keep track of tasks. Everyone should use this to keep each other accountable.

## Glosarry

- PR: Pull request
