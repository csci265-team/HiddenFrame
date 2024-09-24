
# CSCI 265 Project Update (Phase 3)

## Team name: We Be Daves

## Project/product name: See a Neevle, Hear a Neevle

## Contact person

 - Dave Narealdave, nareal@somewhere.ca

## Key revisions since phase 2

There has been one significant functional addition to the product requirements, and a number of fixes/enhancements to the requirements document itself.  Those changes are summarized below.

### Changes to the requirements

During design we realized it might be possible for creatures/projectiles to cross between map zones, and we needed rules around how that would work.  The decision was to maintain an invisible wall at zone boundaries: this would not impede players but would block creatures and projectiles, and could also be used to block the 'wrong' team from entering areas that were designated for one team or the other.

### Changes to the team charter

Davey and Duhyve have swapped understudy roles (Davey taking on testing understudy, Duhyve taking on puzzle and plot understudy).  The charter.md document has been updated to reflect tthis.

### Requirements document updates

The glossary in the requirements document has now been completed.

The map for puzzle zone 2B has been fixed for the noted Gamma gate misplacement.

The detailed text for the Help topics has been added.

A stats/computation page has been added to the end of the document.  This summarizes all the various player and creature stats and computations scattered across the rest of the document, providing a quick-reference aid for development and testing (rather than needing to hunt through the document text to find the correct setting or formula).  This does mean that any future changes to settings/values will need to be reflected in **both** locations in the document.

### Standards document updates

In the version control section: the public github repo information has been added, and a description of the core directory structure of the repo has been added.

