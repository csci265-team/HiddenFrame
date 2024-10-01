
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

Project HiddenFrame is, in brief, a picture board (like Pinterest) that will use various technologies like DBMS, WebRTC, and APIs. It also acts as a secret message board by using steganography. HiddenFrame will be publicly accessible and encourages the general public to share photographic content; meanwhile, select users will be using HiddenFrame's true capabilities to exchange pictures encoded with hidden data. (Which only a select few will know about)

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

### Image wall
As mentioned earlier, HiddenFrame is, in brief, a picture board (like Pinterest). It will be publicly accessible and encourage the general public to share photographic content. 

This photographic content will be visible on the home page of our web app on our "Image wall", which is basically a 3x3 (or make it responsive? stretch goal?) grid of images that "infinitely" scrolls.

### Uploading images

Our web based app will allow users to upload any images they want to our servers, which will then be displayed on our home page image wall. 

This feature will be accessible as a button on our home page right above the image wall.

The public aspect users will have some sort of image upload size limit (tbd).

### Private login
Select users will be using HiddenFrame's true capabilities to exchange pictures embedded with hidden data.

Our web app will have a private login page that will allow this capability. Users will be able to find this page at the `/login` endpoint (subject to change).

This web page will have a simple login form that will ask the user of some sort of identifier (username/email, tbd) and a password (using passkeys is a stretch goal)


### Hiding messages in the pictures

The same web based app will also have a special upload section for private users which will include a text box that allows users to type in a message that will get embedded into their image using steganography. Once the image is embedded we will provide the user with a "key" that can be used to decrypt the message from the image later. 

The text message will have some sort of size limit but we are expecting it to be a high number.

The registered users will be able to access this page after logging in from the aforementioned private login page.

### Creating invites

The private web page will also have a button that allows them to create a set number of invites. These invites will allow the recivers to also create an account for the private aspect.

Once a registered user has created the allocated amount of invites they will not be able to create any more invites.

The registered users will be able to access this page after logging in from the aforementioned private login page.

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

Much like the scaling section in the original proposal, here we must document which features are regarded as essential, which ones are secondary priorities, and which ones are 'nice to have' but low priority for this term.

## 8.Glossary <a name="section8"></a>

Define any product-specific terms and any terms that are unlikely to be known to the 'average' reader (e.g. a random second-year CS student).

TBD: To be decided

## 9.Appendices <a name="section9"></a>

If additional supported documents are needed then append them here

