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
    - 1.1. [User Experience](#11-user-experience)
    - 1.2. [Image Manipulation](#12-image-manipulation)
    - 1.3. [Interconnectivity between Frontend and Backend](#13-interconnectivity-between-frontend-and-backend)
2.  [Metrics to Determine Challenge Completion](#2-metrics-to-determine-challenge-completion)
3.  [Code Required to Meet Challenges](#3-code-required-to-meet-challenges)
4.  [Assessment of Proof Of Concept](#4-assessment-of-proof-of-concept)
5.  [Glossary](#5-glossary)

## 1. Core Technical Challenges
### 1.1. User Experience
### 1.2. Image Manipulation
### 1.3. Interconnectivity between Frontend and Backend
At the start of our project, we divided the team into two groups: the front-end and back-end teams. The front-end team chose to develop in JavaScript, while the back-end team opted for C++. Given these language differences, we needed a reliable way to connect our front-end and back-end services.

After exploring various options, we determined that using a REST API would best suit our needs, as it offers a robust solution for standard client-server interactions, handling data requests and updates efficiently without requiring real-time functionality. This approach would allow our C++ back-end to handle HTTP requests and send data in a format easily rendered by our JavaScript-based front end.

To further simplify development and deployment within our project’s timeline, we also decided to use a full-stack web framework on the front end. This choice provides an integrated environment to streamline both front-end and back-end development, offering a relatively low learning curve for team members.

By combining a REST API on the back end with a full-stack web framework on the front end, we will be able to create a website with a responsive, interactive UI and efficient data handling, delivering the fast, seamless experience we envisioned.
## 2. Metrics to Determine Challenge Completion
### 2.1. Metrics for User Experience
#### 2.1.1 Interactivity
#### 2.1.2 Reactivity
### 2.2. Metrics for Image Manipulation
### 2.3. Metrics for Connectivitiy
## 3. Code Required to Meet Challenges
### 3.1. Determining Frontend Framework
#### 3.1.1. API Compatability
#### 3.1.2. CSS Framework
### 3.2. Image In and Out Operations
### 3.3. API Integration
Due to our system's back end being written in C++ and our front end using a JavaScript framework, we decided to utilize an API server built with the "Crow" framework for creating HTTP and WebSocket web services. We considered other C++ back-end frameworks, such as Boost.Beast, Pistache, and CppCMS, but chose Crow for its lightweight and fast performance, user-friendly design with a smaller learning curve, native support for multithreading, and built-in JSON and WebSocket handling.

For our front end, we opted for the "Remix" framework because of its advanced data-fetching capabilities and modern UI management (expand here with additional reasons for choosing Remix over other frameworks). Using the web "fetch API," we can efficiently handle data requests from both the client and server sides.

With Crow's high-performance, minimalistic approach and Remix's strengths in data management and user interface design, these frameworks form an optimal combination for efficient HTTP requests and delivering a responsive, modern user experience.
## 4. Assessment of Proof Of Concept
### 4.1. Assessment of Frontend
### 4.2. Assessment of Backend
### 4.3. Assessment of API
## 5. Glossary