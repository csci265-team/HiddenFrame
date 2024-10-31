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
    - 2.1. [Metrics for User Experience](#21-metrics-for-user-experience)
        - 2.1.1. [Image Display/Upload](#211-image-displayupload)
        - 2.1.2. [User Interface](#212-user-interface)
3.  [Code Required to Meet Challenges](#3-code-required-to-meet-challenges)
4.  [Assessment of Proof Of Concept](#4-assessment-of-proof-of-concept)
    - 4.1. [Assessment of Frontend](#41-assessment-of-frontend)
5.  [Glossary](#5-glossary)

## 1. Core Technical Challenges

### 1.2. Image Manipulation

No one on our team had past experience with progromatic image manipulation. This will involve stripping an image file of its raw data contents, copying that data into a data structure, and being able to manipulate the values stored in this data structure in such a way that once a series of operations are performed to encode message data, the data stored within the image data structure can still be used to output a new image that looks indistinguishable from the original image. This will require the scheme described more fully in ![5.3 Design - Payload Embedding & Retrieval](./design.md#53-payload-embeddingretrieval), however, this also will involve learning about how image data is stored.

### 1.3. Interconnectivity between Frontend and Backend

## 2. Metrics to Determine Challenge Completion

### 2.1. Metrics for User Experience
The HiddenFrame project is divided into two major parts in terms of front-end. Displaying/Uploading images with or without embedded message (note, that it is crucial for both types of images to be displayed identically in terms of quality, color accuracy, and resolution), and the rest of UI, which includes seamless and comprehensive workflow experience for users and navigation with ease.

#### 2.1.1. Image Display/Upload
For the image display and upload feature, as mentioned above, success will be measured by the frontend’s ability to handle and visually present both encoded and unencoded images with no perceptible differences in quality, color accuracy, or resolution. The goal is to ensure that images embedded with hidden messages appear identical to standard images, maintaining visual integrity. Additionally, the upload process should be straightforward and intuitive, allowing users to easily upload images without experiencing interface disruptions, errors, or quality degradation post-upload.

#### 2.1.2. User Interface
The UI aims to provide a seamless, intuitive experience that guides users effortlessly through the app’s functionality. Success in this metric will be determined by how easily users can navigate between core features (such as scrolling, uploading, and encoding/decoding images) without confusion. The interface should be responsive, providing immediate visual feedback to user actions, such as confirmations for uploads and clear indicators of progress. The UI should also be free of unnecessary complexity, ensuring that users find it easy to complete tasks, even on their first use.

### 2.2. Metrics for Image Manipulation

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

### 3.4. Determining API SMTH

## 4. Assessment of Proof Of Concept

### 4.1. Assessment of Frontend

1. Image Display/Upload Evaluation:
	- Visual Integrity: The frontend generally displays encoded and unencoded images with no discernible visual differences, maintaining quality, color accuracy, and resolution. However, an issue was identified with 4-channel images (those with an alpha channel for transparency). These images may not display the embedded message as intended.
	- Upload Process: Initial testing of the upload process shows that users can upload images without issues or visible quality degradation. 

2.	User UI Evaluation:
	- Navigation and Accessibility: The primary UI components, including navigation between the main features (image upload, encoding, and scrolling), were tested to ensure they provide a smooth, intuitive experience. 
	- Responsiveness and Feedback: Interactive elements (buttons, notifications) provide immediate feedback, contributing to a responsive and engaging user experience. 

3.	Challenges Identified:
	- Load Times: The UI responsiveness is satisfactory in most cases, but load times for displaying images might need optimization in the final implementation.
    - Embedding and displaying a message with 4-channel images might not work correctly and need to be optimized in the final implementation.

### 4.2. Assessment of Backend
Jeremy
### 4.3. Assessment of API

## 5. Glossary
