
# CSCI 265 Requirements and specifications (Phase 2)

## Team name: Project HiddenFrame

## Project/product name: HiddenFrame

## Contact person and email

The following person has been designated the main contact person for questions from the reader:

 - NameA, their@emailaddy

 # Table of Contents
 1. [Introduction and overview](#section1)
 2. [Known issues/omissions](#section2)
 3. [Product features and behavior](#section3)
 4. [User interface and navigation](#section4)
 5. [Use cases/scenarios](#section5)
 6. [Non-functional requirements](#section6)
    - 6.1. [Public  Aspect](#section61)
    - 6.2. [Private Aspect](#section62)
    - 6.3. [Mathematics](#section63)
 1. [Feature prioritization](#section7)
 2. [Glossary](#section8)
 3. [Appendices](#section9)

## 1.Introduction and overview <a name="section1"></a>

Provide the reader with an introduction to the product: its purpose, its core features, what audience it is aimed at and how they'll be using it, and what platform(s) it is targeting.

Project HiddenFrame is, in brief, a picture board (like Pinterest) that will use various technologies like DBMS, WebRTC, and APIs. It also acts as a secret message board by using steganography. HiddenFrame will be publicly accessible and encourage the general public to share photographic content; meanwhile, select users will be using HiddenFrame's true capabilities to exchange pictures encoded with hidden data. (Which only a select few will know about)

It targets the Web platform with a focus on desktop devices first and mobile devices as a strech goal.

If the product has limitations that the user wouldn't expect then those should be mentioned as well.  (For example, if we were building a calculator but it couldn't handle real number calculations then we should probably warn the reader about that.)

## 2.Known issues/omissions <a name="section2"></a>

Currently HiddenFrame will allow uploading images with embedding hidden text messages in the same images.
Our strech goals include:

- Uploading images with secret embedded audio
- Uploading images with secret embedded images
- Uploading videos with secret embedded text
- Uploading videos with secret embedded audio
- Uploading vidoes with secret embedded images


## 3.Product features and behaviour <a name="section3"></a>

This might be much like our original proposal but in far greater detail: we want to thoroughly explain/describe all aspects of the product's functionality: all the features and every aspect of its behaviour.

Here the reader should should be able to find the answer for any question along the lines of
- How do I use feature X?
- How do I enter data value Y?
- What are the limits (if any) on what I enter for Z?
- What does the product do if I enter an incorrect value?
- What happens when I select W?"

This section should be intuitive to follow if the reader is simply reading through the document to learn about the product, but it should also make it easy for the reader to quickly look up the answer to any specific question.

## 4.User interface and navigation <a name="section4"></a>

### Home page 

![A depection of the public home page](<resources/images/HiddenFrame Detailed Home page.png>)
The home page will have all the previously uploaded images by different users.
Provide visual depictions of every screen, menu, drop-down, pop-up, etc.  This isn't intended to be a to-the-pixel exact representation, but it is expected to show all the visible elements and options, and their approximate positions and appearance.

Accompany each visual depiction with a clear description of what it shows and what each visible option represents.

Provide a navigation guide/map and description that show how all the screens/menus etc relate to one another: i.e. clearly showing/describing how the user navigates from screen-to-screen and which screens/choices lead to which others.

## 5.Use cases/scenarios <a name="section5"></a>

Provide use cases detailing the different ways someone might actually want to use the product (e.g. a "sign in" use case, a "check balance" use case, a "make a deposit" use case, etc).

Provide scenarios that illustrate the use cases in a practical example.  (E.g. Bob has $30 to deposit and wants to deposit it, check the balance, and if there is enough then transfer $100 to his savings account, ... then walk through the Bob's actions from sign-in to sign-out.)

## 6.Non-functional requirements <a name="section6"></a>
### 6.1. Public  Aspect <a name="section61"></a>
One of the central pillars of project HiddenFrame is it's social media. HiddenFrame shares many of the non-functional requirements as other social media platforms. Some of the primary concerns of the Public Aspect are:
- User Privacy - HiddenFrame's public site is intended to attract a userbase posting publicly visible photographs. As such we will require a comprehensive disclaimer, permitting the public display of all photos posted to the site. Since, the public site will not (at this time) require account creation no (or minimal) user data will be stored.  
- Data use and Retention - HiddenFrame will have to comply with federal and provincial data protection laws such as the federal [Personal Information Protection and Electronic Documents Act](https://laws-lois.justice.gc.ca/PDF/P-8.6.pdf) and the BC [Personal Information Protection Act](https://www.bclaws.gov.bc.ca/civix/document/id/complete/statreg/03063_01).  
- Moderation - With the anonymous nature of the posts on the public site, it is extremely important that HiddenFrame moderate content to ensure that the pictures on the site are appropriate. 
- Hardware & Networking - Images have a relatively large storage requirement; managing server space in order to accommodate demand may be a challenge. The uploading and downloading of images can also take a significant amount of time; as such a fast internet connection for the server will be required. (The amount of storage space and network speed required will need to be quantified on a per user basis.)
- Image retention period - The permanent storage of images in bulk is unlikely to be viable. As such ProjectHidden frame will only retain images for a set period of time before deletion (exact amount of time TBC).
### 6.2. Private Aspect <a name="section62"></a>
HiddenFrame's other primary feature is the steganography manipulation of images for chosen users. In addition to all of the Public Aspect Non-functional Requirements this part of the project poses its own unique challenges:
- User Privacy - Since this part of the site will require account creation HiddenFrame will have a responsibility to safeguard any user information provided. 
- Steganography keys -  If the decryption keys for image decoding are stored on the HiddenFrame servers (not ideal), they will be secured in order to ensure security.
- Misuse of HiddenFrame for Illegal activity - HiddenFrame will moderate the site for content and co-operate with law enforcement in whatever capacity is required. 
### 6.3. Mathematics <a name="section63"></a>
HiddenFrame's steganographic features require that we develop a method inserting the payload into the carrier, and successfully retrieve the payload back from the carrier. As such we will require The ability to produce 'keys' which will mathematically describe the pixels modified. In order to accomplish this we will utilize the mathematical concept of a "generating set". This concept will allow us to describe the pixels we will be using for steganography.

## 7.Feature prioritization <a name="section7"></a>

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

## 8.Glossary <a name="section8"></a>

Define any product-specific terms and any terms that are unlikely to be known to the 'average' reader (e.g. a random second-year CS student).

## 9.Appendices <a name="section9"></a>

If additional supported documents are needed then append them here

