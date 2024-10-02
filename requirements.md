
# CSCI 265 Requirements and specifications (Phase 2)

## Team name: Project HiddenFrame

## Project/product name: HiddenFrame

## Contact person and email

The following person has been designated the main contact person for questions from the reader:

 - NameA, their@emailaddy

## Introduction and overview

Provide the reader with an introduction to the product: its purpose, its core features, what audience it is aimed at and how they'll be using it, and what platform(s) it is targeting.

Project HiddenFrame is, in brief, a picture board (like Pinterest) that will use various technologies like DBMS, WebRTC, and APIs. It also acts as a secret message board by using steganography. HiddenFrame will be publicly accessible and encourage the general public to share photographic content; meanwhile, select users will be using HiddenFrame's true capabilities to exchange pictures encoded with hidden data. (Which only a select few will know about)

It targets the Web platform with a focus on desktop devices first and mobile devices as a strech goal.

If the product has limitations that the user wouldn't expect then those should be mentioned as well.  (For example, if we were building a calculator but it couldn't handle real number calculations then we should probably warn the reader about that.)

## Known issues/omissions

Currently HiddenFrame will allow uploading images with embedding hidden text messages in the same images.
Our strech goals include:

- Uploading images with secret embedded audio
- Uploading images with secret embedded images
- Uploading videos with secret embedded text
- Uploading videos with secret embedded audio
- Uploading vidoes with secret embedded images


## Product features and behaviour

This might be much like our original proposal but in far greater detail: we want to thoroughly explain/describe all aspects of the product's functionality: all the features and every aspect of its behaviour.

Here the reader should should be able to find the answer for any question along the lines of
- How do I use feature X?
- How do I enter data value Y?
- What are the limits (if any) on what I enter for Z?
- What does the product do if I enter an incorrect value?
- What happens when I select W?"

This section should be intuitive to follow if the reader is simply reading through the document to learn about the product, but it should also make it easy for the reader to quickly look up the answer to any specific question.

## User interface and navigation

### Home page 

![A depection of the public home page](<resources/images/HiddenFrame Detailed Home page.png>)
The home page will have all the previously uploaded images by different users.
Provide visual depictions of every screen, menu, drop-down, pop-up, etc.  This isn't intended to be a to-the-pixel exact representation, but it is expected to show all the visible elements and options, and their approximate positions and appearance.

Accompany each visual depiction with a clear description of what it shows and what each visible option represents.

Provide a navigation guide/map and description that show how all the screens/menus etc relate to one another: i.e. clearly showing/describing how the user navigates from screen-to-screen and which screens/choices lead to which others.

## Use cases/scenarios

Provide use cases detailing the different ways someone might actually want to use the product (e.g. a "sign in" use case, a "check balance" use case, a "make a deposit" use case, etc).

Provide scenarios that illustrate the use cases in a practical example.  (E.g. Bob has $30 to deposit and wants to deposit it, check the balance, and if there is enough then transfer $100 to his savings account, ... then walk through the Bob's actions from sign-in to sign-out.)

## Non-functional requirements

Detail any requirements beyond the actual feature set previously required, e.g.
- safety/security/privacy requirements
- performance requirements (response times, throughput, memory footprint)
- software quality requirements

## Feature prioritization

For some of our team members, this is our first attempt at building a website. For all of our team members, this is our first attempt to create a piece of technology using steganography techniques. The following lists include primary features, secondary features, and stretch goals for the scope of our project.

### Primary Features

The features our team considers mandatory for our project are:
- A webpage for creating a username for select users with access to the secret chat feature;
- A webpage for logging into a username for select users with access to the secret chat feature;
- A webpage for uploading and posting pictures to a public picture-board sharing site;
- A secret webpage for uploading an image (carrier) with a hidden message (payload) that includes a hidden message embedded within the image to send to another user. Initially, the payload will be limited to text. This webpage should also indicate if a user has received any unread secret messages, allow them to read them, and display the image they were embedded within;
- A wall/picture-board sharing webpage to view pictures the user and other users have posted;
- A program running on the server that can be called by the webpage that encodes payloads into carriers and decodes them for the recipient. Initially, this program should be able to encode text into an image using a key system where the key is embedded into the file's data;
- A key generation algorithm that fits a key into a filename of not more than 50 characters; 
- An encoding algorithm that fits not less than 2,000 characters into an image containing at least 30,000 pixels; and
- An invite webpage where select users with access to the secret chat feature may invite others to create a username and utilize the hidden feature(s).

### Secondary Features

Our secondary goals that our team hopes to implement depending on the remaining time available for the creation of this project include:
- A username recovery mechanism;
- One-time read/receive secret messages by removing the decode key from the file's contents;
- The ability to like and comment on pictures on the wall; and
- A separate payload type of chiptune music tones that may be encoded into images with not less than 150,000 pixels.

### Stretch Goals

Our team's stretch goals include that are not expected to make it into our project submission but would be nice to include if all previous items are completed ahead of schedule:
- Using a separate carrier format for both secret text messages and music files;
- Adding support for embedding images as payloads; and
- Utilizing a common encryption standard into the process so that secret messages are encrypted into and decrypted from their payloads and embedded.

## Glossary

Define any product-specific terms and any terms that are unlikely to be known to the 'average' reader (e.g. a random second-year CS student).

## Appendices

If additional supported documents are needed then append them here

