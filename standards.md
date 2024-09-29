
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

Detail the documentation standards and processes to be followed (can provide links to existing industry standards), how they will be enforced, and how they will be reviewed for updating if/as needed.

## Coding standards and processes

Detail the coding standards and processes to be followed (can provide links to existing industry standards), how they will be enforced, and how they will be reviewed for updating if/as needed.

## Version control standards and processes

The git lead will enforce these standards along with everyone else holding each other accountable:

#### Adding to master

Our project has a [`master`](https://github.com/csci265-team/project/tree/master) branch. 
This is the branch that gets submitted at the end of each phase and thus our goal is to keep this branch stable and protected.
Below are some of the explicit rules protecting this branch:

- No pushing directly to [`master`](https://github.com/csci265-team/project/tree/master). Create pull requests instead.
- Pull requests need to be created against [`master`](https://github.com/csci265-team/project/tree/master) to get code merged in.
- At least two team members need to approve changes in a PR before code can be merged into [`master`](https://github.com/csci265-team/project/tree/master).
- The creator of the pull request can not merge their own pull request.
- Force pushes should be avoided.

#### Adding to dev branches

Our project also has "dev" branches (`*-dev`), which will follow the naming convention `nameOfMemeber-dev`.
Each team memeber can make a branch with this naming scheme and the following rules will apply to it:

- Only owner of said branch can push directly to it.
- If someone other than the owner wants to make changes to this type of branch they must make a pull request against it. (`nameOfMemeber-dev` <--- `xyz-branch`)
- The pull request may only be merged after approval from the owner of said branch
- Pull requests need to be created against [`master`](https://github.com/csci265-team/project/tree/master) to get code merged in.
- The creator of the pull request can not merge their own pull request.
- Force pushes should be avoided.

#### Other branchews

Team members may create any number of branches other than the ones mentioned above.
These branches should follow the same standards as the ["dev" branch standards](#adding-to-dev-branches) unless the creator explicitly communicates otherwise.
Some naming reccomendations are given below:
- `feat-*` For branches where any number of team members are working on a certain feature


Teams have been made on GitHub for eaech of the roles in this project.
A project page on GitHub is created to keep track of tasks. This is to be used by everyone to keep each other accountable.
