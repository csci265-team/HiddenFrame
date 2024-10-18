<script
  src="https://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML"
  type="text/javascript">
</script>

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

1.  [Known Omissions](#1-known-omissions)
2.  [Design Overview](#2-design-overview)
3.  [Front-End Design](#3-front-end-design)
    - 3.1. [Public Aspect](#31-public-aspect)
    - 3.2. [Private Aspect](#32-private-aspect)
4.  [Back-End Design](#4-back-end-design)
    - 4.1. [Image Analysis](#41-image-analysis)
    - 4.2. [Key Generation](#42-key-generation)
    - 4.3. [Payload Embedding](#43-payload-embedding)
    - 4.4. [Payload Retrieval](#44-payload-retrieval)
5.  [Network Design](#5-network-design)
6.  [Data Design](#6-data-design)
7.  [Other Design Elements](#7-other-design-elements)
    - 7.1. [Project Directory Structure](#71-project-directory-structure)
8.  [Glossary](#8-glossary)
9.  [Appendixes](#9-appendixes)

# List of Figures

## 1. Known Omissions

## 2. Design Overview

Target Platform: The initial focus will be on desktop browsers for optimal viewing and functionality, with potential for mobile responsiveness as a stretch goal.

- Primary Technology: The front-end will be developed using HTML5, CSS3, and JavaScript. For dynamic elements, React (or another JavaScript framework, if preferred) will be used.
- Frameworks/Libraries: We will use Bootstrap or TailwindCSS for responsive design, ensuring consistent and scalable layouts.
- UI Design Principles:
  - Clean and minimalistic design, with a focus on easy navigation.
  - Clear visual hierarchy to distinguish between public and private features.
  - Intuitive interactions with visual feedback for all user actions (e.g., buttons, image uploads, and secret message decoding).

## 3. Front-End Design

The front-end of HiddenFrame will be responsible for providing a user-friendly interface for both public and private users.

### 3.1 Front-End Configuration

- Node and NPM: For developement we are using node.js and node package manager, since our framework Remix is built on the Web fetch API we will not need to use node.js in production.
- Typescript: TypeScript is used to ensure strict type-checking and cleaner code, especially when handling sensitive functionality like steganographic embedding and decryption.
- Remix: We are using Remix as our frontend framework. Remix is a brand new framework that optimizes performance, simplifies full-stack React development, and efficiently manages data with built-in support for modern web standards and tools. It helps us to focus on the user interface and work back through web standards to create a fast and stable user experience. 
- Vite: Vite is the default build tool for Remix, providing fast development server capabilities and optimized builds, which are important for maintaining the security of the private communication features.
- TailwindCSS: TailwindCSS is being in our project to build responsive layouts for the image grid and other UI elements. We have customized the config file to add our brand colors.
- ESLint: We are using ESLint to enforce clean coding practices to maintain a consistent and error-free codebase for the public-facing UI.

### 3.2. Public Aspect

The public-facing part of the website serves as a picture-sharing platform, allowing users to upload and browse images. This aspect is crucial to attracting a broad user base and providing the platform's visual appeal.

- Main Features:
  - Image Wall: A grid of publicly shared images that scrolls infinitely.
  - Image Upload: A button at the top allows users to upload images to the platform. These images will appear on the public wall after uploading.
  - User Interactions(stretch goal): Users can like, comment on, and share images.
- User Experience:
  - The image wall is designed for ease of use, with images displayed in a 3x3 grid format. Hover effects and clickable icons provide an intuitive interaction model for public users.
  - Responsive Design: The public aspect will be optimized for desktop, with some mobile functionality being a stretch goal.

### 3.3. Private Aspect

The private side of HiddenFrame is accessible only to privileged users who have login credentials. This aspect enables secure communication through hidden messages embedded in images using steganography.

- Main Features:

  - Private Login Page: A dedicated login page for users with access to the hidden messaging system.
  - Secret Message Board: After logging in, users can upload images with hidden messages and decode messages from received images.
  - Invite System: Privileged users can invite others to access the private aspect, creating a controlled environment for hidden communication.

- Security and Privacy:
  - Login Protection: The private login page will be built with security in mind, using HTTPS and appropriate authentication measures.

#### 3.3.1. Image Wall

Image Wall is a grid of publicly shared images that scrolls infinitely. It is designed for ease of use, with images displayed in a 3x3 grid format. Hover effects and clickable icons provide an intuitive interaction model for public users. The image wall uses CSS grid classes to ensure responsivness. Tha data for it is fetched from the back-end API server on page load. Each image is a 16 REM by 16 REM square with 0.5 REM rounded corners. Each image is encapsulated in the anchor tag, which, onve clicked, opens the image in a new tab. The images are shown in order of ascending based on time of creation. 

## 4. Back-End Design

### 4.1. Image Analysis

### 4.2. Key Generation

The purpose of a key is to tell the encoding algorithm where to write the hidden message the sender has provided into an image and to say to the receiver where in the image to look for a hidden message. To generate a key, the following details about the image must be passed to the algorithm as functional input:

1. The number of channels in the image representing which RGBA channels are being used;
2. The (x,y) dimensions of pixels in the image; and
3. The binary string to be encoded into the image.

The message will be broken down into packets of bits that will be passed through the LSBs (Least Significant Bits) of a pixel's channels. For an image using one or two channels, one bit of information will be passed per channel per pixel that has been instructed to be encoded or decoded by the key. For three and four-channel images, the channel will tell the encoder and decoder additional information further described in Payload Embedding and Payload Retrieval. Modifying the LSBs in the channel will ensure that minimal visual changes to the images are made. The purpose of the key will be to tell the encoder and decoder how many pixels need to be skipped within the image when looking for the next significant pixel containing information.  To perform this task, we will use generators of a group of integers mod n.

Suppose an image has n pixels. We want to know, which integers under addition \(mod \\, n\) generate the set \\(\\{0,1,2,3,...,n-1\\}\\).

Definition: Let \\(G=\\{0,1,2,3,...,n-1\\}\\) be a group under the binary option of addition \\(mod n\\). We say that \\(a \\in G\\) generates \\(G\\) if \\(G=\\{ a^n|n \\in Z \\}\\). Note in this context \\(a^n\\) does not mean \\(a\\) to the power of \\(n\\), but rather \\(a\\) added to itself n-times, since the binary operation was addition.

To calculate the generators of \\(n\\), we will iteratively use the Euclidean Algorithm to determine which numbers in the set \\(\\{0,1, 2, 3, ... , n-1\\}\\) are relatively prime to \\(n\\) up to a fixed value \\(k < n\\) if \\(n\\) becomes large. The purpose of going up to only a fixed value \\(k\\), is so that our jumps between pixels do not become so large that we need to pass over the almost the entire image with each pixel selection. To find numbers that are relatively prime to n, we must find integers, \\(i\\), whose \\(gcd(n,i)=1\\).

Next, we will look for a skip size in pixels that accomplishes two competing goals:

1. Allows us to use every pixel in the image if needed should the message become too large; and
2. Maximize the space between pixels containing information to avoid clustering of modified pixels when this can be avoided.

Using any generator as the size of skips between pixels already accomplishes our first goal.  Even if we pass over the image multiple times, we will only land on every pixel exactly once until we land on our hit our first modified pixel. Once we have come back to this position, no further modifications to the image can be made. Utilizing generators will prevent us from colliding with previously modified pixels should we need to pass over the image more than once and will prevent us from wasting any space in the image to modify.

To maximize the space between pixels, we need to know how many pixels must be modified in the image to maximize the space between them. This involves knowing what the bit string contents of our message will be after the characters have been converted to binary. As will be discussed in further detail in Payload Embedding and Payload Retrieval, the channels will be used to encode the bit strings into the images. The binary will be shortened into a format resembling \\(\[2,1,3,0,1,1,...\]\\) that is to be read as two 1's, three 0's, one 1, ... and looks like 110001... in binary. The size of this array divided by 2 will tell us how many pixels must be modified. Using this information, we must look through our list of generators such that the total number of pixels in our image, n, divided by the number of pixels we need to modify should be roughly equal to the generator we choose from our computed list. This will ensure as even of a distribution as possible.  When this is not possible, generators 1, and n-1 should NOT be chosen as they are guaranteed to cause clustering. By this method, suppose we call the generator we've selected \\(g\\).

Now, we need to pass the following information in the key to the encoder and decoder:

1. The size of the skips which was the generator chosen;
2. The number of hex characters used to describe the generator in the key since we would want to obscure this number; and
3. The number of channels used in the image.

We can further obscure the generator \\(g\\) we chose by randomly selecting another generator from our list since any of these numbers can be used to produce any number in \\(\\{0,1,2,3,...,n-1\\}\\), let's call this other generator \\(a\\). Next, we find its multiplicative inverse \\(a^\{-1\}\\) such that \\(aa^\{-1\} \\, mod \\, n=1\\), and finding a number \\(b\\) such that \\(ab \\, mod \\, n = g\\).  We can achieve this by using \\(a^\{-1\}\\) since we can rearrange our equation \\(b=a^\{-1\}g \\, mod \\, n\\). We can repeat this step and find multiple ways of representing \\(g\\).  The purpose of this would be to put several of them into a key and provide us with a way to represent the same skip size in many different ways, increasing the number of unique keys that can be stored to represent images that require the same number of skips within them.  Finally, our keys will have a format like \\(a_1,b_1,a_2,b_2,...G,e,f\\) where:

1. Each ab pairs are hex values that when multiplied together mod n give back the size of the skips;
2. G a terminating character to tell the reader the description of the skips have ceased;
3. \\(e\\) a hex character that describes how many hex digits each \\(a_i or b_i\\) is; and
4. \\(f\\) the number of channels used in the image.

### 4.3. Payload Embedding

### 4.4. Payload Retrieval

## 5. Network Design

## 6. Data Design

## 7. Other Design Elements

### 7.1 Project Directory Structure

## 8. Glossary

## 9. Appendixes
