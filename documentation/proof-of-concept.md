The proof-of-concept document

The intent in this phase is for the team to demonstrate to themselves and the client (instructor) that the project design is feasible, i.e. that the core functionality can be successfully implemented by Dec. 6th following the current design.

To accomplish this, there are four key elements, each of which should be addressed in the document:

Identifying the core technical challenges:
By this point in the design process, the team should be aware of (most of) the major hurdles they will face in implementing their design. This section of the document is intended to outline each of those challenges in sufficient detail to explain the problem and why it is a key area of concern/focus.

Determining what is necessary to demonstrate each challenge can be met:
The goal of this phase is to convince the team and the client(instructor) that the core of the product can be successfully implemented by the due date (Dec. 6th). In this section the intent is to detail specifically how each of the challenges identified above will be met. This might be by implementing a single program that shows all can be met, or by creating a small set of programs demonstrating the challenges being met individually. The documentation here should outline the code components that need to be created, the accompanying assets that need to be created, and any servers/tools that need to be set up/configured.

Producing the code and other assets to meet each challenge:
The team should decide (and document) where the proof of concept elements should reside. It's possible (likely?) that you won't want the proof of concept code mixed in with the rest of the 'real' project code, so the creation of a separate project branch or separate directory in the repo are both possibilities.

    The team should create the necessary code, setup/configure any tools/servers needed, and create any assets needed to perform live demos of the proof of concept.

    The proof of concept document should clearly indicate where the associated code and other elements can be found (typically their branch and location within the team github repository).

    Where tools/servers need any significant setup or configuration, the necessary steps should be documented somewhere in the team repo and the location of that documentation should be noted in the proof-of-concept document.

Assessing the results of the proof-of-concept and any implications:
The proof-of-concepts may or may not be entirely successful, and may actually reveal new challenges the team had not previously been aware of (or had not recognized the full importance of).

    The precise structure of this section will likely vary from team to team, but in it the team should assess:

        how successful the proof of concept was,
        which concerns it successfully addressed plus any it failed to address and why,
        how the team plans to address any remaining concerns (e.g. changes to the requirements and/or design, different approaches to the implementation, backup plans if the concerns continue to be an implementation problem).
        <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<DELETE ABOVE HERE>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

# CSCI 265 Proof Of Concept (Phase 4)

## Team name: Project HiddenFrame

## Project/product name: HiddenFrame

## Contact person and email

# Table of Contents

1.  [Core Technical Challenges](#1-core-technical-challenges)
2.  [Metrics to Determine Challenge Completion](#2-metrics-to-determine-challenge-completion)
3.  [Code Required to Meet Challenges](#3-code-required-to-meet-challenges)
4.  [Assessment of Proof Of Concept](#4-assessment-of-proof-of-concept)
5.  [Glossary](#5-glossary)

## 1. Core Technical Challenges

### 1.2. Image Manipulation
Our team did not initially have any foundational understanding of image manipulation. Dealing with images requires reading and interpreting not only the raw information but dealing with various file formats with their attendant headers/footers. 

Some formats of images provide built in compression (such as JPG), our program needs to be able to either implement a solution that will work on compressed images, or find a way to circumvent the problem. 

Since we need to manipulate specific channels of the pixels in the image, and alter them only slightly, We will require the ability to manipulate individual bits within a images raw data. This is not an aspect of C++ programing that has thus far not been covered. 

No one on our team had past experience with progromatic image manipulation. This will involve stripping an image file of its raw data contents, copying that data into a data structure, and being able to manipulate the values stored in this data structure in such a way that once a series of operations are performed to encode message data, the data stored within the image data structure can still be used to output a new image that looks indistinguishable from the original image. This will require the scheme described more fully in ![5.3 Design - Payload Embedding & Retrieval](./design.md#53-payload-embeddingretrieval), however, this also will involve learning about how image data is stored.

### 1.3. Interconnectivity between Frontend and Backend

## 2. Metrics to Determine Challenge Completion

### 2.1. Metrics for User Experience

#### 2.1.1 Interactivity

#### 2.1.2 Reactivity

### 2.2. Metrics for Image Manipulation
There are two primary metrics for successful image manipulation. The first is the integrity of the payload message. Anything less that 100% successful encoding and decoding of data will result in corruption of the payload. The second important metric for image manipulation is the visible difference between an encodeded and unecoded image. Our target here is that an encoded image is not significantly visibly different; we shall consider this to be successful if a user cannot distinguish between an encoded and unencoded image.

### 2.3. Metrics for Connectivitiy

## 3. Code Required to Meet Challenges

### 3.1. Determining Frontend Framework
We decided to use the "Remix" framework for our front-end. Remix offers several advantages that influenced our decision:

1. **Modern and Innovative**: Remix is a relatively new framework that provides an opportunity to learn and work with cutting-edge technologies.
2. **Server-Side Rendering (SSR)**: Remix employs advanced SSR techniques, which enhance performance and improve the development experience.
3. **Powered by React**: Remix is built on top of React, similar to Next.js, which is widely adopted and trusted in the industry. This ensures a robust and familiar development environment.
4. **Potential for Mass Adoption**: Given its innovative features and strong foundation, Remix has the potential to gain widespread adoption, making it a valuable skill for developers.
5. **Built on Fetch API**: The Remix build is fully compatible with the Fetch API, making it highly adaptable and ready to be deployed anywhere, including edge environments.

By choosing Remix, we aim to leverage its modern capabilities to build a high-performance and maintainable front-end application.

#### 3.1.1. API Compatability

### 3.2. User Experience

To maintain a consistent UX we have decided to use tailwindcss. Tailwindcss allows us to quickly create great looking designs.

#### 3.2.1. Colors

We will be using a simplistic design language. We are using the following two colors as part of our theme:

- <font color="#F3E3BF">#F3E3BF</font>
- <font color="#553829">#553829</font>

#### 3.2.2. Themes

We will also be maintaining two themes, a "dark" and a "light" theme. Since we will be using tailwindcss this task is really easy. Each component will first be styled for the "light" theme and then we will just invert the colors using the tailwind [`dark:`](https://tailwindcss.com/docs/dark-mode) selector.

#### 3.2.3. Components

We have decided to componentize our design elements, each of our elements will be split out into their own seperate file. For example the "Button" component will be located at [`/apps/web/app/components/Button.tsx`](https://github.com/csci265-team/project/blob/master/apps/web/app/components/Button.tsx)

This approach promotes reusability and reduces redundancy. We won't have to go and modify each and every occurance of a component instead we can just modify the main component file.

### 3.3. Image In and Out Operations
In order to simplify the reading and writing of images, our team elected to use two C header libraries stb_image and stb_image_write. These two libraries provide our project with the ability to deal directly with raw image data, in the form of char arrays. This abstracts us from most of the concerns surrounding file formatting. The code we use to confirm this feature set is working is test_image_io.cpp. This test file calls the two constructors, and write_image class methods from the image_class.cpp. These functions show that HiddenFrame can read a file from the filesystem or as live data passed to it from the API server, and write images to the file system. This corresponds to tests 1,2, and 4 of the image system tests. 

Dealing with lossy file formats (JPG) in our case, meant that we had a choice of trying to modify our encoding algorithm to deal with compression or circumvent the problem in some manner. In our case we decided to (at least temporarily) provide full image read capabilities, but when we store the images we will only be doing so in lossless formats. This functionality is part of the image_class's write_image method. This is demonstrated by image system test 3. 

Our final challenge was coding a capability to confirm that we could manipulate the individual channels of the image, and successfully store and retrieve data (in the format our compression algorithm lays out). This merely required the use of C++'s bit shifting operators and a careful application of the algorithm. We implemented this as the modify_image and retrieve_payload functions. This challenge is demonstrated by image system test 5.  

### 3.4. Determining API SMTH

## 4. Assessment of Proof Of Concept

### 4.1. Assessment of Frontend

### 4.2. Assessment of Backend
Jeremy
### 4.3. Assessment of API

## 5. Glossary
