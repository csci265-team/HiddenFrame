# CSCI 265 Proof Of Concept (Phase 4)

## Team name: Project HiddenFrame

## Project/product name: HiddenFrame

## Contact person and email

# Table of Contents

# Table of Contents

1.  [Core Technical Challenges](#1-core-technical-challenges)
    - 1.1. [Implementing Frontend](#11-implementing-frontend)
    - 1.2. [Image Manipulation](#12-image-manipulation)
    - 1.3. [Interconnectivity between Frontend and Backend](#13-interconnectivity-between-frontend-and-backend)
2.  [Metrics to Determine Challenge Completion](#2-metrics-to-determine-challenge-completion)
    - 2.1. [Metrics for User Experience](#21-metrics-for-user-experience)
      - 2.1.1. [Image Display/Upload](#211-image-displayupload)
      - 2.1.2. [User Interface](#212-user-interface)
    - 2.2. [Metrics for Image Manipulation](#22-metrics-for-image-manipulation)
    - 2.3. [Metrics for Connectivity](#23-metrics-for-connectivity)
3.  [Code Required to Meet Challenges](#3-code-required-to-meet-challenges)
    - 3.1. [Determining Frontend Framework](#31-determining-frontend-framework)
    - 3.2. [User Experience](#32-user-experience)
      - 3.2.1. [Colors](#321-colors)
      - 3.2.2. [Themes](#322-themes)
      - 3.2.3. [Components](#323-components)
    - 3.3. [Image In and Out Operations](#33-image-in-and-out-operations)
    - 3.4. [API Integration](#34-api-integration)
4.  [Assessment of Proof Of Concept](#4-assessment-of-proof-of-concept)
    - 4.1. [Assessment of Frontend](#41-assessment-of-frontend)
    - 4.2. [Assessment of Backend](#42-assessment-of-backend)
    - 4.3. [Assessment of API](#43-assessment-of-api)
5.  [Glossary](#5-glossary)

## 1. Core Technical Challenges

### 1.1. Implementing Frontend

Our team was well prepared when it came to the frontend. One of our main challenges was selecting the right frontend framework. After careful consideration, we chose Remix (a detailed explanation of this choice is provided in [3.1. Determining Frontend Framework](#31-determining-frontend-framework)).

Another challenge we encountered was determining how to style the frontend. We wanted a solution that ensured a smooth developer experience without compromising on design quality. TailwindCSS emerged as the ideal choice, offering extensive customization options alongside a great developer experience.

### 1.2. Image Manipulation

No one on our team had past experience with programmatic image manipulation. Dealing with images requires reading and interpreting not only the raw information but also dealing with various file formats with their attendant headers/footers. This required implementing the scheme described more fully in ![5.3 Design - Payload Embedding & Retrieval](./design.md#53-payload-embeddingretrieval).

Some formats of images provide built-in compression (such as JPEG). Our program needs to be able to either implement a solution that will work on compressed images or find a way to circumvent the problem of the image being compressed after embedding.

Since we need to manipulate specific channels of the pixels in the image and alter them only slightly, we will require the ability to manipulate individual bits within an image’s raw data. This is not an aspect of C++ programming that has thus far not been covered in our CSCI courses.

### 1.3. Interconnectivity between Frontend and Backend

At the start of our project, we divided the team into two groups: the front-end and back-end teams. The front-end team chose to develop in JavaScript, while the back-end team opted for C++. Given these language differences, we needed a reliable way to connect our front-end and back-end services.

After exploring various options, we determined that using a REST API would best suit our needs, as it offers a robust solution for standard client-server interactions, handling data requests and updates efficiently without requiring real-time functionality. This approach would allow our C++ back-end to handle HTTP requests and send data in a format easily rendered by our JavaScript-based front end.

To further simplify development and deployment within our project’s timeline, we also decided to use a full-stack web framework on the front end. This choice provides an integrated environment to streamline both front-end and back-end development, offering a relatively low learning curve for team members.

By combining a REST API on the back end with a full-stack web framework on the front end, we will be able to create a website with a responsive, interactive UI and efficient data handling, delivering the fast, seamless experience we envisioned.

## 2. Metrics to Determine Challenge Completion

### 2.1. Metrics for User Experience

The HiddenFrame project is divided into two major parts in terms of front-end. Displaying/uploading images with or without embedded messages (note that it is crucial for both types of images to be displayed identically in terms of quality, color accuracy, and resolution), and the rest of the UI, which includes a seamless and comprehensive workflow experience for users and navigation with ease.

#### 2.1.1. Image Display/Upload

For the image display and upload feature, as mentioned above, success will be measured by the frontend’s ability to handle and visually present both encoded and unencoded images with no perceptible differences in quality, color accuracy, or resolution. The goal is to ensure that images embedded with hidden messages appear identical to standard images, maintaining visual integrity. Additionally, the upload process should be straightforward and intuitive, allowing users to easily upload images without experiencing interface disruptions, errors, or quality degradation post-upload.

#### 2.1.2. User Interface

The UI aims to provide a seamless, intuitive experience that guides users effortlessly through the app’s functionality. Success in this metric will be determined by how easily users can navigate between core features (such as scrolling, uploading, and encoding/decoding images) without confusion. The interface should be responsive, providing immediate visual feedback to user actions, such as confirmations for uploads and clear indicators of progress. The UI should also be free of unnecessary complexity, ensuring that users find it easy to complete tasks, even on their first use.

### 2.2. Metrics for Image Manipulation

There are two primary metrics for successful image manipulation. The first is the integrity of the payload message. Anything less than 100% successful encoding and decoding of data will result in corruption of the payload. The second important metric for image manipulation is the visible difference between an encoded and unencoded image. Our target here is that an encoded image is not significantly visibly different; we shall consider this to be successful if a user cannot distinguish between an encoded and unencoded image.

### 2.3. Metrics for Connectivitiy

To ensure optimal performance and user experience, we would be monitoring the following key metrics for connectivity:

- Latency: The time taken by a data packet travelling from one place to another. We would be measuring the round-trip time of these data packets travelling from the user's computer to the servers where the website will be hosted. Our target is to maintain an average latency of 200ms for 97% of the user connection while browsing through our website (excluding image upload with a hidden message).
- Response size refers to the total amount of data sent from the server to the client in response to a request. Larger response sizes require more data to be transferred, directly affecting the throughput and loading times. We are aiming to reduce the response size as much as possible, which would in turn improve the loading speed and reduce the load on the servers. We will also try to implement caching.
- Image upload success rate: This metric is key for us to measure how reliable and fast our image upload process has become, more so because of the added complexity in embedding secret messages through steganography. Higher success rates mean fewer retries, due to which we can also reduce the load on servers and bandwidth consumption. Our target is to maintain a success rate of 90% or higher.

  $$\text{Success Rate} = \frac {\text{successful uploads}}{\text{total upload attempts}}*100\\%$$

- Time complexity of the steganography algorithm: To calculate the time complexity, we would first need to figure out the problem size. Theoretically, if the message is larger than the image, we would not be able to encode it. Therefore, the problem size would be the size of the message. Furthermore, this algorithm is also dependent on the keying algorithm, which iterates through each pixel of the image to find the pixels which could be easily modified such that the image doesn't change drastically. So the worst case would be O(NM), where N is the size of the message to be encoded and M is the size of the image. We would have to optimize these algorithms so that uploading pictures with messages embedded in them is as fast as uploading regular media.

## 3. Code Required to Meet Challenges

### 3.1. Determining Frontend Framework

We decided to use the "Remix" framework for our front-end. Remix offers several advantages that influenced our decision:

1. **Modern and Innovative**: Remix is a relatively new framework that provides an opportunity to learn and work with cutting-edge technologies.
2. **Server-Side Rendering (SSR)**: Remix employs advanced SSR techniques, which enhance performance and improve the development experience.
3. **Powered by React**: Remix is built on top of React, similar to Next.js, which is widely adopted and trusted in the industry. This ensures a robust and familiar development environment.
4. **Potential for Mass Adoption**: Given its innovative features and strong foundation, Remix has the potential to gain widespread adoption, making it a valuable skill for developers.
5. **Built on Fetch API**: The Remix build is fully compatible with the Fetch API, making it highly adaptable and ready to be deployed anywhere, including edge environments.

By choosing Remix, we aim to leverage its modern capabilities to build a high-performance and maintainable front-end application.

### 3.2. User Experience

To maintain a consistent UX, we have decided to use Tailwindcss. Tailwindcss allows us to quickly create great-looking designs.

#### 3.2.1. Colors

We will be using a simplistic design language. We are using the following two colors as part of our theme:

- <font color="#F3E3BF">#F3E3BF</font>
- <font color="#553829">#553829</font>

#### 3.2.2. Themes

We will also be maintaining two themes, a "dark" and a "light" theme. Since we will be using tailwindcss this task is really easy. Each component will first be styled for the "light" theme, and then we will just invert the colors using the tailwind [`dark:`](https://tailwindcss.com/docs/dark-mode) selector.

#### 3.2.3. Components

We have decided to componentize our design elements; each of our elements will be split out into its own separate file. For example, the "Button" component will be located at [`/apps/web/app/components/Button.tsx`](https://github.com/csci265-team/project/blob/master/apps/web/app/components/Button.tsx).

This approach promotes reusability and reduces redundancy. We won't have to go and modify each and every occurrence of a component; instead, we can just modify the main component file.

### 3.3. Image In and Out Operations

In order to simplify the reading and writing of images, our team elected to use two C header libraries stb_image and stb_image_write. These two libraries provide our project with the ability to deal directly with raw image data, in the form of char arrays. This abstracts us from most of the concerns surrounding file formatting. The code we use to confirm this feature is test_image_io.cpp. This test file calls the two constructors and write_image class methods from the image_class.cpp. These functions show that HiddenFrame can read a file from the filesystem or as live data passed to it from the API server and write images to the file system. This corresponds to tests 1, 2, and 4 of the image system tests.

Dealing with lossy file formats (JPG) in our case meant that we had a choice of trying to modify our encoding algorithm to deal with compression or circumvent the problem in some manner. In our case, we decided to (at least temporarily) provide full image read capabilities, but when we store the images, we will only be doing so in lossless formats. This functionality is part of the image_class's write_image method. This is demonstrated by image system test 3.

Our final challenge was coding a capability to confirm that we could manipulate the individual channels of the image and successfully store and retrieve data (in the format our compression algorithm lays out). This merely required the use of C++'s bit shifting operators and a careful application of the algorithm. We implemented this as the modify_image and retrieve_payload functions. This challenge is demonstrated by image system test 5.

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

From our proof of concept for how messages can be embedded and retrieved, we have been able to successfully embed and read bitstrings encoded into an image with minimal visual changes made to the image. In our final product, we expect to be able to use an image analysis tool to see how different the encoded image is from the original. We learned from this that on the retrieval of a message from an image, we need a stopping condition. When embedding a message, we know how long the message is, but this is unknown when retrieving the image. For this reason, we create a stopping bit in the embedding process where a skip is performed after the final bit or set of bits is embedded to a pixel and the next bit's LSBs in all channels of the pixel are set to 0.

Additionally, when finding the multiplicative inverse of an element a in a $Z_n$ set, we have found that our initial algorithm can take longer than expected to run depending on two factors, how large $n$ is, and how large the multiplicative inverse $a^{-1}$ happens to be. The closer $a^{-1}$ is to ${n-1}$, the longer the algorithm takes to run. While our current implementation of checking whether $a*a^{-1} \\, mod \\, n=1$ in a while loop works, we may look at ways to speed up this process.

### 4.3. Assessment of API

We will be using Postman to carry out extensive testing and monitoring of our API to guarantee its reliability, performance, and especially the steganography-enabled image upload feature.

#### 4.3.1. Testing

- Postman makes it easier to write and execute test cases. Postman Collections are essentially portable sets of API requests that we will be using to execute the test cases systematically. To automate the tests, we will be using Postman’s built-in testing features, such as pm.test for writing assertions.

  Different types of tests:

  - Functional tests which verify that the API endpoints (e.g., upload, retrieve, delete images) are behaving as expected.
  - Validation tests ensure that the inputs and outputs conform to the expected formats and constraints (e.g., image file types, size limits).
  - Boundary tests are to test the edge cases to ensure the API can handle maximum and minimum values, as well as invalid inputs gracefully.

- Through Postman, we can make environments which are basically collections of variables that we can manage centrally, making it easier to switch between different setups (e.g., development, staging). Setting up different environments will boost our testing efficiency as we could easily switch between different environments without modifying the requests.
- To load test, Postman can simulate load by having multiple parallel virtual users hit our endpoints. Using this method, we can observe how the API performs under stress and measure the response time to ensure that they meet the required benchmarks.

#### 4.3.2. Monitoring

Postman plots the graph for the above-discussed metrics, which makes it easier to visualize performance data. It also can set up periodic health checks for our API endpoints to ensure they are up and running. This involves sending a simple request to each endpoint and checking the status code. A 200 status code indicates that the API is functioning correctly. We can also configure alerts sent to our emails, which would notify us of any critical issues in the time of automated test runs.

## 5. Glossary