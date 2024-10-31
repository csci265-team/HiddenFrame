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
    - 2.1. [Metrics for User Experience](#21-metrics-for-user-experience)
        - 2.1.1. [Image Display/Upload](#211-image-displayupload)
        - 2.1.2. [User Interface](#212-user-interface)
3.  [Code Required to Meet Challenges](#3-code-required-to-meet-challenges)
4.  [Assessment of Proof Of Concept](#4-assessment-of-proof-of-concept)
    - 4.1. [Assessment of Frontend](#41-assessment-of-frontend)
5.  [Glossary](#5-glossary)

## 1. Core Technical Challenges

### 1.1. Implementing Frontend

### 1.2. Image Manipulation
Our team did not initially have any foundational understanding of image manipulation. Dealing with images requires reading and interpreting not only the raw information but dealing with various file formats with their attendant headers/footers. 

Some formats of images provide built in compression (such as JPG), our program needs to be able to either implement a solution that will work on compressed images, or find a way to circumvent the problem. 

Since we need to manipulate specific channels of the pixels in the image, and alter them only slightly, We will require the ability to manipulate individual bits within a images raw data. This is not an aspect of C++ programing that has thus far not been covered. 

No one on our team had past experience with progromatic image manipulation. This will involve stripping an image file of its raw data contents, copying that data into a data structure, and being able to manipulate the values stored in this data structure in such a way that once a series of operations are performed to encode message data, the data stored within the image data structure can still be used to output a new image that looks indistinguishable from the original image. This will require the scheme described more fully in ![5.3 Design - Payload Embedding & Retrieval](./design.md#53-payload-embeddingretrieval), however, this also will involve learning about how image data is stored.

### 1.3. Interconnectivity between Frontend and Backend
At the start of our project, we divided the team into two groups: the front-end and back-end teams. The front-end team chose to develop in JavaScript, while the back-end team opted for C++. Given these language differences, we needed a reliable way to connect our front-end and back-end services.

After exploring various options, we determined that using a REST API would best suit our needs, as it offers a robust solution for standard client-server interactions, handling data requests and updates efficiently without requiring real-time functionality. This approach would allow our C++ back-end to handle HTTP requests and send data in a format easily rendered by our JavaScript-based front end.

To further simplify development and deployment within our project’s timeline, we also decided to use a full-stack web framework on the front end. This choice provides an integrated environment to streamline both front-end and back-end development, offering a relatively low learning curve for team members.

By combining a REST API on the back end with a full-stack web framework on the front end, we will be able to create a website with a responsive, interactive UI and efficient data handling, delivering the fast, seamless experience we envisioned.

## 2. Metrics to Determine Challenge Completion

### 2.1. Metrics for User Experience
The HiddenFrame project is divided into two major parts in terms of front-end. Displaying/Uploading images with or without embedded message (note, that it is crucial for both types of images to be displayed identically in terms of quality, color accuracy, and resolution), and the rest of UI, which includes seamless and comprehensive workflow experience for users and navigation with ease.

#### 2.1.1. Image Display/Upload
For the image display and upload feature, as mentioned above, success will be measured by the frontend’s ability to handle and visually present both encoded and unencoded images with no perceptible differences in quality, color accuracy, or resolution. The goal is to ensure that images embedded with hidden messages appear identical to standard images, maintaining visual integrity. Additionally, the upload process should be straightforward and intuitive, allowing users to easily upload images without experiencing interface disruptions, errors, or quality degradation post-upload.

#### 2.1.2. User Interface
The UI aims to provide a seamless, intuitive experience that guides users effortlessly through the app’s functionality. Success in this metric will be determined by how easily users can navigate between core features (such as scrolling, uploading, and encoding/decoding images) without confusion. The interface should be responsive, providing immediate visual feedback to user actions, such as confirmations for uploads and clear indicators of progress. The UI should also be free of unnecessary complexity, ensuring that users find it easy to complete tasks, even on their first use.

### 2.2. Metrics for Image Manipulation
There are two primary metrics for successful image manipulation. The first is the integrity of the payload message. Anything less that 100% successful encoding and decoding of data will result in corruption of the payload. The second important metric for image manipulation is the visible difference between an encodeded and unecoded image. Our target here is that an encoded image is not significantly visibly different; we shall consider this to be successful if a user cannot distinguish between an encoded and unencoded image.

### 2.3. Metrics for Connectivitiy
To ensure optimal performance and user experience, we would be monitoring the following key metrices for connectivity:
- Latency: The time taken by a data packet travelling from one place to other. We would be measuring the round-trip time of these data packets travelling from user's computer to the servers where the website will be hosted. Our target is to maintain an average latency of 200ms for 97% of the user connection while browsing through our website (excluding image upload with a hidden message).
- Response size refers to the total amount of data sent from the server to the client in response to a request. Larger response sizes require more data to be transferred, directly affecting the throughput and loading times. We are aiming to reduce the response size as much as possible, which would intern improve the loading speed and reduce the load on the servers. We also will try to implement caching.
- Image upload success rate: This metric is key for us to measure how reliable and fast our image upload process has become more so because of the added complexity in embedding secret messages through steganography. Higher success rates mean fewer retries due to which we can also reduce the load on servers and bandwidth consumption. Our target is to maintain a success rate of 90% or higher.

    $$
    Success\ \ Rate = \frac {successful\ \ uploads}{total\ \ upload\ \ attempts}\ 100\%
    $$

- Time complexity of the steganography algorithm: To calculate the time complexity, we would first need to figure out the problem size. Theoretically, if the message is larger than the image, we would not be able to encode it. Therefore the problem size would be the size of the message. Furthermore, this algorithm is also dependent on keying algorithm which iterating through each pixel of the image to find the pixels which could be easily modified such that the image doesn't change drastically. So the worst case would be O(NM) where N is the size of the message to encoded and M is the size of the image. We would have to optimize these algorithms so that uploading pictures with messaage embedded in them is as fast as uploading regular media.
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
In order to simplify the reading and writing of images, our team elected to use two C header libraries stb_image and stb_image_write. These two libraries provide our project with the ability to deal directly with raw image data, in the form of char arrays. This abstracts us from most of the concerns surrounding file formatting. The code we use to confirm this feature, is test_image_io.cpp. This test file calls the two constructors, and write_image class methods from the image_class.cpp. These functions show that HiddenFrame can read a file from the filesystem or as live data passed to it from the API server, and write images to the file system. This corresponds to tests 1,2, and 4 of the image system tests. 

Dealing with lossy file formats (JPG) in our case, meant that we had a choice of trying to modify our encoding algorithm to deal with compression or circumvent the problem in some manner. In our case we decided to (at least temporarily) provide full image read capabilities, but when we store the images we will only be doing so in lossless formats. This functionality is part of the image_class's write_image method. This is demonstrated by image system test 3. 

Our final challenge was coding a capability to confirm that we could manipulate the individual channels of the image, and successfully store and retrieve data (in the format our compression algorithm lays out). This merely required the use of C++'s bit shifting operators and a careful application of the algorithm. We implemented this as the modify_image and retrieve_payload functions. This challenge is demonstrated by image system test 5.  

### 3.4. API Integration
Due to our system's back end being written in C++ and our front end using a JavaScript framework, we decided to utilize an API server built with the "Crow" framework for creating HTTP and WebSocket web services. We considered other C++ back-end frameworks, such as Boost.Beast, Pistache, and CppCMS, but chose Crow for its lightweight and fast performance, user-friendly design with a smaller learning curve, native support for multithreading, and built-in JSON and WebSocket handling.

For our front end, we opted for the "Remix" framework because of its advanced data-fetching capabilities and modern UI management (expand here with additional reasons for choosing Remix over other frameworks). Using the web "fetch API," we can efficiently handle data requests from both the client and server sides.

With Crow's high-performance, minimalistic approach and Remix's strengths in data management and user interface design, these frameworks form an optimal combination for efficient HTTP requests and delivering a responsive, modern user experience.
## 4. Assessment of Proof Of Concept

### 4.1. Assessment of Frontend

1. Image Display/Upload Evaluation:
	- Visual Integrity: The frontend generally displays encoded and unencoded images with no discernible visual differences, maintaining quality, color accuracy, and resolution.
	- Upload Process: Initial testing of the upload process shows that users can upload images without issues or visible quality degradation. 

2. User UI Evaluation:
	- Navigation and Accessibility: The primary UI components, including navigation between the main features (image upload, encoding, and scrolling), were tested to ensure they provide a smooth, intuitive experience. 
	- Responsiveness and Feedback: Interactive elements (buttons, notifications) provide immediate feedback, contributing to a responsive and engaging user experience. 

3. Challenges Identified:
	- Load Times: The UI responsiveness is satisfactory in most cases, but load times for displaying images might need optimization in the final implementation.

### 4.2. Assessment of Backend
Jeremy
### 4.3. Assessment of API
We will be using Postman to carry out extensive testing and monitoring of our API to guarantee its reliability, performance, and especially the steganography-enabled image upload feature.

#### 4.3.1. Testing

- Postman makes it easier to write and execute test cases. Postman Collections are essentially portable sets of API requests that we will be using to execute the test cases systematically. To automate the tests, we will be using Postman’s built-in testing features, such as pm.test for writing assertions. 

    Different types of tests:
    - Functional tests which verifies that the API endpoints (e.g., upload, retrieve, delete images) are behaving as expected.
    - Validation tests ensures that the inputs and outputs conform to the expected formats and constraints (e.g., image file types, size limits).
    - Boundary tests are to test the edge cases to ensure the API can handle maximum and minimum values, as well as invalid inputs gracefully.

- Through Postman we can make environments which are basically collection of variables that we can manage centrally, making it easier to switch between different setups (e.g., development, staging). Setting up different environment will boost our testing efficiency as we could easily switch between different environment without modifying the requests.
- To load test, Postman can simulate load by having multiple parallel virtual users hit our endpoints. Using this method we can observe how the API performs under stress, and measure the response time to ensure that they meet the required benchmarks.

#### 4.3.2. Monitoring
Postman plots the graph for the above discussed matrics which make it easier to visualize these performance data. It also can set-up periodic health checks our API endpoints to ensure they are up and running. This involves sending a simple request to each endpoint and checking the status code. A 200 status code indicates the API is functioning correctly. We can also configure alerts sent to our emails which would notify us of any critical issues in the time of automated test runs.
## 5. Glossary
