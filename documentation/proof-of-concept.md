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
### 1.1. User Experience
### 1.2. Image Manipulation
### 1.3. Interconnectivity between Frontend and Backend
## 2. Metrics to Determine Challenge Completion
### 2.1. Metrics for User Experience
#### 2.1.1 Interactivity
#### 2.1.2 Reactivity
### 2.2. Metrics for Image Manipulation
### 2.3. Metrics for Connectivitiy
To ensure optimal performance and user experience, we would be monitoring the following key metrices for connectivity:
- Latency: The time taken by a data packet travelling from one place to other. We would be measuring the round-trip time of these data packets travelling from user's computer to the servers where the website will be hosted. Our target is to maintain an average latency of 200ms for 97% of the user connection.
- Response size refers to the total amount of data sent from the server to the client in response to a request. Larger response sizes require more data to be transferred, directly affecting the throughput and loading times. We are aiming to reduce the response size as much as possible, which would intern improve the loading speed and reduce the load on the servers. We also will try to implement caching.
- Image upload success rate: This metric is key for us to measure how reliable and fast our image upload process has become more so because of the added complexity in embedding secret messages through steganography. Higher success rates mean fewer retries due to which we can also reduce the load on servers and bandwidth consumption. Our target is to maintain a success rate of 90% or higher.
    $$
    Upload Success Rate = \frac {successful\ \ uploads}{total\ \ upload\ \ attempts}\, 100\%
    $$
- Time complexity of the steganography algorithm: To calculate the time complexity, we would first need to figure out the problem size. Theoretically, if the message is larger than the image, we would not be able to encode it. Therefore the problem size would be the size of the message. Furthermore, this algorithm is also dependent on keying algorithm which iterating through each pixel of the image to find the pixels which could be easily modified such that the image doesn't change drastically. So the worst case would be O(NM) where N is the size of the message to encoded and M is the size of the image.
## 3. Code Required to Meet Challenges
### 3.1. Determining Frontend Framework
#### 3.1.1. API Compatability
#### 3.1.2. CSS Framework
### 3.2. Image In and Out Operations
### 3.3. Determining API SMTH
## 4. Assessment of Proof Of Concept
### 4.1. Assessment of Frontend
### 4.2. Assessment of Backend
### 4.3. Assessment of API
## 5. Glossary