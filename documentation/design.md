The design document

As with phase 2, there is a substantial amount of work associated with this phase and the choices made will have significant implications for the rest of the project - start early, work carefully, and be sure the whole team is in agreement with the decisions made.

As a general rule, all documents should adhere to high standards of writing quality, including spell checking, grammatical correctness, consistent layouts/formats, appropriate use of footnotes, appendices, glossaries, tables/figures/diagrams, citations, etc.

Before work starts on the implementation (coding), we want to ensure a clean design has been agreed upon by all team members, and that we have documented our design in a single shared resource (the design.md file).

This will be the largest and most fundamental document for this phase of the project, and involves documenting in detail both the logical and physical design of the product.

The document is the one your team (and the instructor and other readers) will be using as a reference point when they need to decide how/what the final product code elements are supposed to be doing/implementing, so needs to be well organized, consistent, and as complete, up to date, and error free as possible. (Your team will be responsible for keeping the document up to date as the project progresses and you refine your ideas on the product design.)

The actual format of the document is left largely to the team's discretion, but discussion of the expected content is provided below, and the lecture material covers a variety of ideas and approaches to design modeling.

However the document is actually structured/ordered, the following information (at a minimum) needs to be present:

    The team and project name, contact info (the contact info is just a single point of contact in case a reader has questions or feedback)

    A table of contents (optional but nice to have)

    A design overview
    This provides an intuitive overview of the high level logical design, preferably with a context diagram (the top level DFD), and also of the key transformations/decisions that will be needed when going from the logical design to an implementation.

    The logical design
    In the logical design we need to specify the decomposition of our system into smaller components from a logical (code-independent) perspective. The logical design should reflect either a layered/top-down approach or an object-oriented approach (or a hybrid of the two), clearly describing the division of the overall system into key components, then clearly describing the decomposition of those, etc. as needed.

    A medium-sized project might involve dividing the overall system into several interacting subsystems, dividing each subsystem into several interacting modules, dividing each module into a number of interacting components, etc.

    Since different subsystems/modules/components will likely be developed by different people, it is important that as a team we clearly establish the responsibilities of each element and how they will interact with others. Thus for each level of decomposition I generally recommend the inclusion of a data flow diagram (DFD), with clear supporting explanation.

    Each element of the system (i.e. each subsystem, module, component, etc) should contain clear, easily referenced descriptions of:
        its overall purpose
        each of the services it provides for other elements of the same DFD level (what will it implement that is used by other portions of the system?)
        - this should show the information exchanged during that process
        the interactions between it and the user(s) and any other external systems
        any persistent data it will need to store, giving each data component a name and identifying the type and restrictions on the data (e.g. "vehicle weight will be stored as a non-negative real number of kilos, rounded to the nearest kilo) 

    As discussed in lectures, we are seeking a division into elements that are cohesive yet loosely coupled, and we want to ensure that all aspects of the overall product functionality are captured somewhere within our design.

    The transition from the logical design to an implementation
    Eventually we'll need to map the elements of our logical design to actual codable entities.

    This section isn't expected to be rigorously completed for phase 3, but the goal is to have an organized start/outline (something we can build off of in phase 4 to get implementation underway).

    Key elements to consider include:
        identifying the programming language(s) and any supporting tools to be used
        identifying the directory and file naming structure to be used within the code repository: identifying the files/directories/subdirectories we use to store the different actual code elements
        identifying the implementation method for each shared data store (database, file, etc), including format, fields, layout
        identifying the interface for all public services provided by the element:
        - publicly accessible/shared data types and fixed/constant values
        - publicly callable routines, what they return, what they'll expect as parameters
        - classes/objects to be used, their key public fields and methods
        This gets close to the level of code skeletons, but does not yet need to be expressed as actual code in the target language(s). 

    A glossary: This is optional but often nice to have: if a term is specific to the product or is unlikely to be known by the average reader (e.g. a random second year CS student) then include an entry for it.

    Any appendices (if/as needed) 

Note that all elements of all figures/diagrams should be clearly described/referenced in the associated text. 
[SAMPLE DOCUMENT LINK](http://csci.viu.ca/~wesselsd/courses/csci265/project/sample_docs/logicaldesign.pdf)

==================================================================
DELETE ALL ABOVE HERE

# CSCI 265 Logical Design (Phase 3)

## Team name: Project HiddenFrame

## Project/product name: HiddenFrame

## Contact person and email
The following person has been designated the main contact person for questions from the reader:

 - Patrick Candy candy.pat@gmail.com

Alternate contact person:

 - Jeremy Shumuk admin@payrollinsights.ca

 # Table of Contents
 1. [Known Omissions](#1-known-omissions)
 2. [Design Overview](#2-design-overview)
 3. [Front-End Design](#3-front-end-design)
    - 3.1. [Public Aspect](#31-public-aspect)
    - 3.2. [Private Aspect](#32-private-aspect)
 4. [Back-End Design](#4-back-end-design)
    - 4.1. [Image Analysis](#41-image-analysis)
    - 4.2. [Key Generation](#42-key-generation)
    - 4.3. [Payload Embedding](#43-payload-embedding)
    - 4.4. [Payload Retrieval](#44-payload-retrieval)
 5. [Network Design](#5-network-design)
 6. [Data Design](#6-data-design)
 7. [Other Design Elements](#7-other-design-elements)
    - 7.1. [Project Directory Structure](#71-project-directory-structure) 
 8. [Glossary](#8-glossary)
 9. [Appendixes](#9-appendixes)

 # List of Figures

 ## 1. Known Omissions

 ## 2. Design Overview
 Target Platform: The initial focus will be on desktop browsers for optimal viewing and functionality, with potential for mobile responsiveness as a stretch goal.
 - Primary Technology: The front-end will be developed using HTML5, CSS3, and JavaScript. For dynamic elements, React (or   another JavaScript framework, if preferred) will be used.
 - Frameworks/Libraries: We will use Bootstrap or TailwindCSS for responsive design, ensuring consistent and scalable layouts.
 - UI Design Principles:
    - Clean and minimalistic design, with a focus on easy navigation.
    - Clear visual hierarchy to distinguish between public and private features.
    - Intuitive interactions with visual feedback for all user actions (e.g., buttons, image uploads, and secret message decoding).

 ## 3. Front-End Design
 The front-end of HiddenFrame will be responsible for providing a user-friendly interface for both public and private users.
 ### 3.1. Public Aspect
 The public-facing part of the website serves as a picture-sharing platform, allowing users to upload and browse images. This aspect is crucial to attracting a broad user base and providing the platform's visual appeal.

 - Main Features:
    - Image Wall: A grid of publicly shared images that scrolls infinitely.
    - Image Upload: A button at the top allows users to upload images to the platform. These images will appear on the public wall after uploading.
    - User Interactions(stretch goal): Users can like, comment on, and share images.
 - Front-End Configuration:
    - Remix: We are using Remix as our frontend framework. Remix is a brand new framework that optimizes performance, simplifies full-stack React development, and efficiently manages data with built-in support for modern web standards and tools. It helps us to focus on the user interface and work back through web standards to create a fast and stable user experience. 
    - TailwindCSS: TailwindCSS is being in our project to build responsive layouts for the image grid and other UI elements. We have customized the config file to add our brand colors.
    - ESLint: We are using ESLint to enforce clean coding practices to maintain a consistent and error-free codebase for the public-facing UI.
 - User Experience:
    - The image wall is designed for ease of use, with images displayed in a 3x3 grid format. Hover effects and clickable icons provide an intuitive interaction model for public users.
    - Responsive Design: The public aspect will be optimized for desktop, with some mobile functionality being a stretch goal.
 
 ### 3.2. Private Aspect
 The private side of HiddenFrame is accessible only to privileged users who have login credentials. This aspect enables secure communication through hidden messages embedded in images using steganography.

 - Main Features:
    - Private Login Page: A dedicated login page for users with access to the hidden messaging system.
    - Secret Message Board: After logging in, users can upload images with hidden messages and decode messages from received images.
    - Invite System: Privileged users can invite others to access the private aspect, creating a controlled environment for hidden communication.
- Front-End Configuration:
    - tsconfig.json: TypeScript is used to ensure strict type-checking and cleaner code, especially when handling sensitive functionality like steganographic embedding and decryption.
    - vite.co: Vite is the chosen build tool for the private aspect, providing fast development server capabilities and optimized builds, which are important for maintaining the security of the private communication features.
    - package.json & package-lock.json: These files manage the dependencies and ensure consistent behavior across environments, particularly for handling encryption libraries and file uploads.
- Security and Privacy:
    - Login Protection: The private login page will be built with security in mind, using HTTPS and appropriate authentication measures.

 ## 4. Back-End Design
 ### 4.1. Image Analysis
 ### 4.2. Key Generation
 ### 4.3. Payload Embedding
 ### 4.4. Payload Retrieval 

 ## 5. Network Design

 ## 6. Data Design

 ## 7. Other Design Elements
 ### 7.1 Project Directory Structure

 ## 8. Glossary

 ## 9. Appendixes
