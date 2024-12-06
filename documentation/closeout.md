# CSCI 265 Close Out (Phase 6)

## Team name: Team HiddenFrame

## Project/product name: HiddenFrame

# Table of Contents

1.  [End State of the Product](#10-end-state-of-the-product)
    - 1.1 [Successfully Incorporated Features](#11-successfully-incorporated-features)
    - 1.2 [Features Not Implemented](#12-features-not-implemented)
2.  [Review of Organization](#20-review-the-organization)
3.  [Review the technical aspects of the project](#30-review-the-technical-aspects)
4.  [End State of the Product](#40-end-state-of-the-product)

## 1.0 End state of the product

### 1.1. Successfully Incorporated Features

- Image wall (Users are able to see uploaded pictures on the main page).
- Uploading images (Users are able to upload images on the main page).
- Registration (Invited users are able to create a profile).
- Login (Users that have been invited by other privileged users and have registered are able to log in).
- Hiding messages in the pictures (Privileged users are able to embed hidden messages).
- Creating invites (Priveleged users are able to invite other users).
- Changing password (Privileged users are able to change their password).
- Logout (Priveleged users are able to logout of their profile).
- Seeing a hidden message (Priveleged users are able to decode embedded messages from the picture, if there is any).
- Changing a theme (Users can choose between dark and light theme).
- Enlarged image (Users are able to see a larger version of pictures).

### 1.2 Features Not Implemented

We have not limited the character count in a message to the max value described in the requirements document (1,024 characters). Our primary focus was to get the system working before coming back to meet this requirement. Additionally, we did not implement any of our secondary features or stretch goals. These included:

- A username recovery mechanism;
- One-time read/receive secret messages by removing the decode key from the file's contents;
- A separate payload type of chiptune music tones that may be encoded into images with not less than 150,000 pixels;
- Using a separate carrier format for both secret text messages and music files;
- The ability to like and comment on pictures on the wall;
- Adding support for embedding images as payloads; and
- Utilizing a common encryption standard into the process so that secret messages are encrypted into and decrypted from their payloads in addition to being embedded into the file.

## 2.0 Review the Organization

The overall team structure and roles/responsibilities we initially assigned for HiddenFrame worked fairly well throughout the span of the project. The primary area where our organizational choices did not serve us well was in the division of labour and time management for the coding of the project. While the documentation was, for the most part, completed in a timely and high-quality manner, our coding fell largely on only a few members of the team. In retrospect a few choices that might have more evenly divided the coding tasks would be:

- Instead of breaking the team into two subgroups (frontend and backend), A better approach might have been performing a rough decomposition of the main modules of the product at conception; then assigning those modules to team members.

- Instead of only requiring a deliverables for the project documentation throughout the course of the project, we should have self-imposed a timeline and deliverables for project modules.

- Immediately after completing the requirements document, we should have begun work on developing test code.

A few other organizational choices we made that were underutilized or hampered our project:

- The group meeting on Thursday afternoons; was partially successful but a 2nd meeting perhaps over discord or organized small group programing sessions might have been helpful.

- Explicit assignment of reviewer's for the git submission policies may have been useful.

## 3.0 Review the Technical Aspects

Much of the packages that we used to do the specific jobs they are designed for, for example, we were happy with Node, SQLite, etc. One topic that came up within group discussion was implementing C++ for db_operations.cpp, which was a steep learning curve. If given the opportunity again, we would have used a language better suited to this task; however, we decided on C++ for this project because of the team's prior experience in this language.

Additionally, we would have spent more time in the planning phase before implementing ideas. For instance, when embedding text into images, we later developed as a concept a simpler and more space-efficient way to embed text into images. If given the opportunity to repeat the project, we would have embedded single bits into all LSBs of the channels of a pixel selected for modification. In the best case, this would have resulted in no difference/improvements (i.e. the bitstring contains consecutive ones or zeros matching the number of channels in an image). However, when in practical scenarios when the bit pattern keeps alternating, we would have been able to embed more text in the worst cases. We had already implemented the logic we decided on earlier and did not have time to change it. This was also not our primary concern since the current logic was performing adequately.

