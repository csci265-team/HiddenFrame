
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

HiddenFrame is a unique platform that can be defined as a public picture-sharing board with hidden communication possibilities. The project is built around the idea of creating an otherwise innocent and visually appealing platform where people can share their pictures. From the user's perspective, HiddenFrame is no different from such websites as Pinterest. Users can browse pictures posted by other people and also share their own media. The public nature of the project intends to encourage as many people to participate and share their content. However, beneath this seemingly ordinary exterior lies a sophisticated system for secure, hidden communication. This system relies on a combination of various steganographic techniques to embed a message within shared images. This design makes HiddenFrame a dual-purpose system, where a relatively busy public platform serves as a cover for a covert communication medium.

Technical Implementation:
- Robust Database Management System (DBMS) for efficient data storage and retrieval
- WebRTC integration for real-time communication and potential peer-to-peer functionality
- API integrations to enhance platform features and connectivity

The unique way that HiddenFrame obfuscates hidden messages opens up a wide range of possible applications:
- Journalism: HiddenFrame provides a secure channel for communicating with those providing vital sources and information to the world’s newspapers, making sure that both the whistleblower and their mission stay protected and secretive.
- Law enforcement: HiddenFrame also provides a channel for the communication with undercover agents and secret informants, ensuring their safety and security while still being able to deliver vital information.
- Penetration testing: One can also use HiddenFrame to simulate the use of a steganographic hidden channel between a theoretical enemy and a real law enforcement agency. This way, the ability to detect the misuse of a image-based steganographic channel in a real life scenario can be tested and evaluated.

Project HiddenFrame will launch on desktop first, but is intended for the web platform, that provides best experience and features for users on large screens. This makes it possible to incorporate advanced features and a richer user experience, both of which can be difficult on mobile. The desktop-first approach focuses on building for the power and screen real estate, especially to help people share and engage around photographic products, so users get what looks/feels like a continuous and consistent experience.

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

Much like the scaling section in the original proposal, here we must document which features are regarded as essential, which ones are secondary priorities, and which ones are 'nice to have' but low priority for this term.

## 8.Glossary <a name="section8"></a>

Define any product-specific terms and any terms that are unlikely to be known to the 'average' reader (e.g. a random second-year CS student).

## 9.Appendices <a name="section9"></a>

If additional supported documents are needed then append them here

