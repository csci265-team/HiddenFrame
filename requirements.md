
# CSCI 265 Requirements and specifications (Phase 2)

## Team name: Project HiddenFrame

## Project/product name: HiddenFrame

## Contact person and email

The following person has been designated the main contact person for questions from the reader:

 - NameA, their@emailaddy

## Introduction and overview

HiddenFrame is a unique platform that can be defined as a public picture-sharing board with hidden communication possibilities. The project is built around the idea of creating an otherwise innocent and visually appealing platform where people can share their pictures. From the user's perspective, HiddenFrame is no different from such websites as Pinterest. Users can browse pictures posted by other people and also share their own media. The public nature of the project intended to encourage as many people to participate and share their content. However, beneath this seemingly ordinary exterior lies a sophisticated system for secure, hidden communication. This system relies on a combination of various steganographic techniques to embed a message within shared images. This design makes HiddenFrame a dual-purpos system, where a relatively busy public platform serves as a cover for a covert communication medium.

Technical Implementation:
- Robust Database Management System (DBMS) for efficient data storage and retrieval
- WebRTC integration for real-time communication and potential peer-to-peer functionality
- API integrations to enhance platform features and connectivity

The unique way that HiddenFrame obfuscates hidden messages opens up a wide range of possible applications:
- Journalism: HiddenFrame provides a secure channel for communicating with those providing vital sources and information to the world’s newspapers, making sure that both the whistleblower and their mission stay protected and secretive.
- Law enforcement: HiddenFrame also provides a channel for the communication with undercover agents and secret informants, ensuring their safety and security while still being able to deliver vital information.
- Penetration testing: One can also use HiddenFrame to simulate the use of a steganographic hidden channel between a theoretical enemy and a real law enforcement agency. This way, the ability to detect the misuse of a gdb-based channel in a real life scenario can be tested and evaluated.

Project HiddenFrame aims at desktop first but for web platform, that allows to provide best experience and features for users on large screens. This makes it possible to incorporate advanced features and a richer user experience, both of which can be difficult on mobile. The desktop-first approach focuses on building for the power and screen real estate, especially to help people share and engage around photographic products, so users get what looks/feels like a continuous and consistent experience.

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

Much like the scaling section in the original proposal, here we must document which features are regarded as essential, which ones are secondary priorities, and which ones are 'nice to have' but low priority for this term.

## Glossary

Define any product-specific terms and any terms that are unlikely to be known to the 'average' reader (e.g. a random second-year CS student).

## Appendices

If additional supported documents are needed then append them here

