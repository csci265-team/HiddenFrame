# CSCI 265 User Acceptance Testing (Phase 5)

## Team name: Team HiddenFrame

## Project/product name: HiddenFrame

---

Test compoent lead:

- Artem: UI & User Account Control
- Yagna: API
- Amitoj: encoding/decoding
- Patrick: Universal testing
- Jeremy: Keys & Image I/O

---

# Table of Contents

1.  [Known Issues](#10-known-issues)
2.  [The Test Plan](#20-the-test-plan)
    - 2.1  [Testing Overview](#21-testing-overview)
    - 2.2  [Key Front-End Testing Challenges](#22-key-front-end-testing-challenges)
    - 2.3 [Key Back-End Testing Challenges](#23-key-back-end-testing-challenges)
    - 2.4 [Testing Timeline](#24-testing-timeline)
    - 2.5 [Test Process](#25-test-process)
    - 2.6 [Test Cases Summary and Organization](#26-test-cases-summary-and-organization)
    - 2.7 [Test Case List](#27-test-case-list)
3. [User Action Scripts](#30-user-action-scripts)
    - 3.1 [User009: Successful Registration](#31-user009-successful-registration)
    - 3.2 [User013: Successful Login](#32-user013-successful-login)
    - 3.3 [User014: Duplicate Username Registration](#33-user014-duplicate-username-registration)
    - 3.4 [User015: Invalid Username Login](#34-user015-invalid-username-login)
    - 3.5 [User016: Invalid Password Login](#35-user016-invalid-password-login)
    - 3.6 [User017: Missing Username Login](#36-user017-missing-username-login)
    - 3.7 [User018: Missing Password Login](#37-user018-missing-password-login)
    - 3.8 [User019: Missing Username Registration](#38-user019-missing-username-registration)
    - 3.9 [User020: Missing Password Registration](#39-user020-missing-password-registration)
    - 3.10 [Image001: Test Load And Write JPG From File System](#310-image001-test-load-and-write-jpg-from-file-system)
    - 3.11 [Image002: Test Load And Write PNG From File System](#311-image002-test-load-and-write-png-from-file-system)
    - 3.12 [Image005: Test Image Embedding And Retrieval](#312-image005-test-image-embedding-and-retrieval)
4.  [Automated Testing](#40-automated-testing)
    - 4.1 [Backend Automated Testing](#41-backend-automated-testing)
    - 4.2 [Frontend Automated Testing](#42-frontend-automated-testing)
    - 4.3 [Full Cycle Tests](#43-full-cycle-tests)
    - 4.4 [Registration Tests](#44-registration-tests)
    - 4.5 [Main Page Tests](#45-main-page-tests)
5.  [Software Tools and Environment](#50-software-tools-and-environment)
    - 5.1 [Version Control and Branch Structure](#51-version-control-and-branch-structure)
    - 5.2 [Directory and File Structure and Content](#52-directory-and-file-structure-and-content)
    - 5.3 [Independent Subsystems and External Resources](#53-independent-subsystems-and-external-resources-project-webdatabase-servers)
6. [Appendix: Detailed Test Case Descriptions](#60-appendix-detailed-test-case-descriptions)

## 1.0 Known Issues

For the complete list of the tests we've thought of so far and have been able to document, see the Test Case List in this document.  Given the time constraints of this project, we recognize the tests we've provided are by no means an exhaustive list that would be expected to be provided to a client upon the delivery of a product in a real-world scenario. For this reason, we have chosen to focus on test cases that are related to key features of the product, and not ones that would certainly be performed before the final delivery of a product but may go completely unnoticed by the client and are only of concern to the development team. Additionally, not all test cases described in the Test Case List have been scripted.

## 2.0 The Test Plan

The testing of HiddenFrame requires 3 overarching tests to be performed. The functionality of the backend needs to be confirmed. In order to do so, we need to measure the performance of several sub-components.

In particular, the backend needs to be tested to confirm:

- The Image I/O operations are successful for images of varying sizes and formats.
- Image Encoding/Decoding is successful on varying image sizes and formats, with messages of various sizes.
- User Authentication is successful/unsuccessful corresponding to username/password combinations.
- User invitations and signup processes correctly make users and track who invited them.
- Revoking user status works correctly.

The 'frontend' testing will also require a suite of particular tests including:

- Successful display of UI elements.
- Responsiveness to user input.
- Correct display of resources to users.
- Successful utilization of UAC to allow authorized users to the private section.
- Successful UAC denial of unauthorized users to the private section, privileged information (payloads), and privileged features (encoding/decoding).

The two systems must also work together, so a whole system test should examine all of the components that each of the above tests describes as well as:

- Communication using the API server is correct and responsive.
- The front end can access all appropriate to user permission features.
- Confirm that HiddenFrame works in a client-server configuration (i.e., works over a LAN), and that the communication is secured (HTTPS).

### 2.1 Testing Overview

All of the various required tests will run, at a minimum, in a Windows and in a Macintosh environment. Further testing utilizing Linux, Android, or other operating systems will be considered and attempted with time permitting. Each of the test suites will be designed based off of the requirements.md and will be generated by team members who did not directly create the driver code for the module under test. The various test cases and challenges will be described in the sections pertaining to their overarching test plan. The testing schedule can be seen in section Testing Timeline.

### 2.2 Key Front-End Testing Challenges

Key frontend testing challenges included deciding whether or not to attempt automated frontend testing. Testing a GUI using code presents greater coding challenges than testing backend functional output given known parameters. Another testing challenge included thinking about how we could include load times and other real-world considerations. In its current state, HiddenFrame runs locally in a browser and not on the web. Imagining how our current implementation could be tested for real-world metrics like load times, screen size considerations, and other real-user situations like performance with accessibility features proved difficult to conceptualize.

### 2.3 Key Back-End Testing Challenges

Key back-end challenges included determining whether tests would be manual or automated, the testing framework to use, and the makefile structure. As stated in known omissions, we are aware that the test list we have compiled is by no means exhaustive, so determining which types of tests to prioritize both in terms of conceptualizing and implementing where possible also proved challenging given that we wanted to use this opportunity to both gain insight into how we could improve our code in its current state while also thinking about test cases that were reflective of the goals set out in the requirements document.

### 2.4 Testing Timeline

Each week, the team would meet twice for periodic code review with a focus on improving code usability and redundancy. This could include making functions data-type agnostic to allow for more types of payload embedding in future versions of the product. Team members will also fix bugs as they appear in tests.

December 6 - 27, 2024 - All team members focus on conceptualizing more test cases because we recognize the cases we currently have are a non-exhaustive list, with each team member continuing to focus on their current section(s) outlined at the beginning of this document. Amitoj, Artem, and Yagna use this time to decide on a front-end automated-testing suite since Boost is not typically used for testing GUIs and implementing HiddenFrame to run as a functional website. Patrick and Jeremy develop subsystem tests for backend systems, including image I/O and the image and user databases. (200 hours cumulative).

Code review - Week 1: December 6 - 13, 2024 - API frameworks.
Code review - Week 2: December 14 - 27, 2024 - User database operations and Image I/O operations.

December 28, 2024 - January 10, 2025 - The team continues writing code not previously conceptualized or included in this document or not yet implemented, with Amitoj, Artem, and Yagna focusing on front-end test code and Jeremy and Patrick focusing on back-end module test code. The frontend team focuses on subsystem tests and then module tests on the frontend server, webpages, and API Server. The backend team focuses on module tests for Image I/O, including key generation, payload embedding and retrieval, and the user and image databases (200 hours cumulative).

Code review - Weeks 3 & 4: December 28, 2024 - January 10, 2025 - Front-end design.

January 11 - 24, 2025: Both teams begin writing unit tests with the backend team to focus on the image manipulation and retrieval, image manipulation and embedding, and key generation modules, namely image_class.cpp and utils.cpp files.  The front-end team will focus on the websites unit test code.  During this time, we are reviewing the user acceptance tests, subsystem tests, and module tests in code review.

January 25 - February 7, 2025 - Continue reviewing module tests and writing unit tests with the front-end to focus on the API server in api.cpp and the backend to focus on the user and image databases in db_operations.cpp.

February 7 - 14, 2025 - Code review of unit tests and final bug fixes.

### 2.5 Test Process

Testers should have admin access to Project HiddenFrame as well as admin access to their machines they're running & testing the product on, in the event they need to rebuild the product, or enter any sudo commands when doing so. Testers will also need to have the following dependancies installed via a package manager on their machines:

- gcc 14.2.0_1 or later,
- asio 1.30.2 or later,
- sqlite 3.47.0 or later, &
- node 23.3.0 or later.


The intent of this section is to ensure the reader understands the process the testers will follow with each of the different types of test. This section should provide an overview of
the general roles/responsibilities of the testers,
the general test environment, tools, and infrastructure used,
the typical setup process prior to running a test case,
the typical process for running a test case,
the typical process for evaluating and reporting on a test case,
any details needed to ensure the test process adheres to the version control process laid out in the team standards.
This is essentially a high level/intuitive summary of the remaining sections of the document.

### 2.6 Test Cases Summary and Organization

The test cases have been split into three primary components, testing user iteraction with the database with tests labelled User###, tests invovling image manipulation with tests labelled ImageI/O###, and tests involving the key generation lablled Keys###.

### 2.7 Test Case List

| Test #  | Requirement(s) Section|Description                                                                                                                                                                                                                                                                                                                                                     |
| ------- | - |---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| User001 | [4.2](../documentation/requirements.md#42-login-page) | Create an invalid username with more than one "@" characters. Username should not be created.                                                                                                                                                                                                                                          |
| User002 | [4.2](../documentation/requirements.md#42-login-page) | Create an invalid username with more than one "." characters after the singular "@" character. Username should not be created.                                                                                                                                                                                                         |
| User003 | [4.2](../documentation/requirements.md#42-login-page) | Create an invalid username where the first character in the username is an "@" character (ie no user before the @domain). Username should not be created.                                                                                                                                                                              |
| User004 | [4.2](../documentation/requirements.md#42-login-page) | Create an invalid username with no "@" character (ie no indication of where the @domain begins). Username should not be created.                                                                                                                                                                                                       |
| User005 | [4.2](../documentation/requirements.md#42-login-page) | Create an invalid username with no "." after the singular "@" character (ie no indication of where .com .ca .other after the @domain begins). Username should not be created.                                                                                                                                                          |
| User006 | [4.2](../documentation/requirements.md#42-login-page) | Create an invalid username with no "a-z" characters between the singular "@" and singular trailing "." characters (no domain in @domain). Username should not be created.                                                                                                                                                              |
| User007 | [4.2](../documentation/requirements.md#42-login-page) | Create an invalid username with no "a-z" characters after the singular "." character following the singular "@" character (ie no indication of .com .ca .other type). Username should not be created.                                                                                                                                 |
| User008 | [4.2](../documentation/requirements.md#42-login-page) | Create a special character (!@#$%^&\*()\_-+=) appears after the "." character following the singular "@" character. Username should not be created.                                                                                                                                                                                    |
| User009 | [4.2](../documentation/requirements.md#42-login-page) | Create a valid user account using an email address. User should be added.                                                                                                                                                                                                                                                              |
| User010 | [3.5](../documentation/requirements.md#35-creating-invites) | Create five valid user accounts from invites from the valid user account in User008 test. The five users should be added.                                                                                                                                                                                                              |
| User011 | [3.5](../documentation/requirements.md#35-creating-invites) | Attempt the creation of a sixth user account as an invite from a valid user account in User008 test. The sixth invite should not be created.                                                                                                                                                                                                                                                                                                                                                                                                                         |
| User012 | [3.5](../documentation/requirements.md#35-creating-invites) | Remove the inviter account from which the invitee was created for User009 test. Confirm both the users in tests User009 and User010 have been removed.                                                                                                                                                                                                        |
| User013 | [4.2](../documentation/requirements.md#42-login-page) | Successfully login as a privleged user.                                                                                                                                                                                                        |
| User014 | [4.2](../documentation/requirements.md#42-login-page) | Attempt to create a duplicate user with the same credentials as test User009. The user should not be created.                                                                                                                                                                                               |
| User015 | [4.2](../documentation/requirements.md#42-login-page) | Attempt to login with an incorrect username. The user should not be logged in.                                                                                                                                                                                                |
| User016 | [4.2](../documentation/requirements.md#42-login-page) | Attempt to login with an incorrect password. The user should not be logged in.                                                                                                                                                                                                |
| User017 | [4.2](../documentation/requirements.md#42-login-page) | Attempt to login with no username entered. The user should not be logged in.                                                                                                                                                                                                |
| User018 | [4.2](../documentation/requirements.md#42-login-page) | Attempt to login with no password entered. The user should not be registerred.                                                                                                                                                                                                |
| User020 | [4.2](../documentation/requirements.md#42-login-page) | Attempt to register with no password entered. The user should not be registerred.                                                                                                                                                                                                |
| User019 | [4.2](../documentation/requirements.md#42-login-page) | Attempt to register with no username entered. The user should not be logged in.                                                                                                                                                                                                |
| ImageI/O001 | [3.2](../documentation/requirements.md#32-uploading-images) | Upload a supported JPG image. The image should upload successfully. Tests a supported format.     |
| ImageI/O002 | [3.2](../documentation/requirements.md#32-uploading-images) | Upload a supported PNG image. The image should upload successfully. Tests a supported format.     |
| ImageI/O003 | [3.2](../documentation/requirements.md#32-uploading-images) | Upload a supported JPG and PNG image. The JPG will be converted to a PNG but the images should not be equal. Required as JPGs are lossy. Confirms using a JPG can work as a payload carrier once it has been converted.   |
| ImageI/O004 | [3.2](../documentation/requirements.md#32-uploading-images) | Test reading an image from a simulated livestream. Should read succesfully. Part of dev testing, outside of requirements.  |
| ImageI/O005 | [3.4](../documentation/requirements.md#34-hiding-messages-in-the-pictures) | Test embedding and retrieval. Attempts to embed the message "Hello World!" into an image. Message should be embedded into the image with minimal change to the image.  |
| ImageI/O006 | [3.4](../documentation/requirements.md#34-hiding-messages-in-the-pictures) | Upload an image containing 40,000 pixels. The image should upload successfully. Tests the lower limit of an acceptable image size.          |
| ImageI/O007 | [3.4](../documentation/requirements.md#34-hiding-messages-in-the-pictures) | Upload an image containing 39,999 pixels.  The image should not upload successfully and an error should be displayed. Tests the lower limit of an acceptable image size.           |
| ImageI/O008 | [3.4](../documentation/requirements.md#34-hiding-messages-in-the-pictures) | Upload an image containing 2,147,483,648 pixels.  The image should upload successfully. Tests the upper limit for an acceptable image size. |
| ImageI/O009 | [3.4](../documentation/requirements.md#34-hiding-messages-in-the-pictures) | Upload an image containing 2,147,483,649 pixels.  The image should not upload successfully and an error should be displayed. Tests the upper limit for an acceptable image size. |
| ImageI/O010 | [3.2](../documentation/requirements.md#32-uploading-images) | Upload a file that is not a supported image file (uploading a .txt file).  The file should not upload successfully and an error message should be displayed. Tests attempting uploading an unsupported format. |
| Keys001 | [7.1](../documentation/requirements.md#71-primary-features) | Generating a key for an image/message with more than the maximum number of characters. Should return a throw error.                                                                                                                                                                                                                    |
| Keys002 | [7.1](../documentation/requirements.md#71-primary-features) | Generating a key for a message with the minimum number of characters. Should return a valid key.                                                                                                                                                                                                                                       |
| Keys003 | [7.1](../documentation/requirements.md#71-primary-features) | Generating a key for a message with the maximum number of characters. Should return a valid key.                                                                                                                                                                                                                                       |
| Keys004 | [7.1](../documentation/requirements.md#71-primary-features) | Generating two keys for identical images and messages 500,000 times and calculate the number of times the keys match. Should generate unique valid keys for both carriers/payloads.                                                                                                                                                                                                             |
| Keys005 | [6.3](../documentation/requirements.md#63-mathematics) & [7.1](../documentation/requirements.md#71-primary-features) | Generating two keys for identical images and messages 500,000 times and calculate the number of times the keys match. Should generate unique valid keys for both carriers/payloads.  Verify the time efficency of the key generation portion only (not the string matching). No key should take longer than 7 seconds and the average time per key should be less than 5 seconds. Verify that all keys are less than 50 characters each.                                                                                                                                            |
| Keys006 | [7.1](../documentation/requirements.md#71-primary-features) | Generating a key for an image that is greater than the maximum allowed image size ((2^{31}) pixels). Should return a throw error.                                                                                                                                                                                                      |
| Keys007 | [6.3](../documentation/requirements.md#63-mathematics) | Generating a key for an image that is of the minimum size (3 pixels for a 4 channel image, with one 8-bit character of all 0s or all 1s, plus the stopping pixel). Should generate a valid key. Used for backend testing.                                                                                                                                        |
| Keys008 | [6.3](../documentation/requirements.md#63-mathematics) | Generating a key for an image that is the minimum size (4 pixels for a 3-channel image, with one 8-bit character of all 0s or all 1s, plus the stopping pixel). Should generate a valid key. Used for backen testing.                                                                                                                                           |
| Keys009 | [6.3](../documentation/requirements.md#63-mathematics) | Generating a key for an image that is the minimum size (9 pixels for a 2-channel image, with one 8-bit character of any pattern, plus the stopping pixel). Should generate a valid key. Used for backend testing.                                                                                                                                                |
| Keys010 | [6.3](../documentation/requirements.md#63-mathematics) | Generating a key for an image that is the minimum size (9 pixels for a 1-channel image, with one 8-bit character of any pattern, plus the stopping pixel). Should generate a valid key.                                                                                                                                                |
| Keys011 | [7.1](../documentation/requirements.md#71-primary-features) | Generating a key for an image that is of the maximum pixel size ($2^{31}$) for any valid character length. Should generate a valid key.                                                                                                                                                                                           |

---
## 3.0 User Action Scripts

### 3.1 User009: Successful Registration

**Description:** Verifies successful user registration with valid credentials.  
**Pre-requisites:** None.  
**Steps:**

1. Navigate to `http://localhost:5173/register/admin`.
2. Enter `correctUsername` in the **Username** field.
3. Enter `correctPassword` in the **Password** field.
4. Click the **Submit** button.
5. Wait for the page to load and observe the URL.  
   **Expected Outcome:** The user is redirected to `http://localhost:5173/login`.

---

### 3.2 User013: Successful Login

**Description:** Verifies successful login with valid credentials.  
**Pre-requisites:** Must follow **UAS001** (registration).  
**Steps:**

1. Navigate to `http://localhost:5173/login`.
2. Enter `correctUsername` in the **Username** field.
3. Enter `correctPassword` in the **Password** field.
4. Click the **Submit** button.
5. Wait for the page to load and observe the URL.  
   **Expected Outcome:** The user is redirected to `http://localhost:5173`.

---

### 3.3 User014: Duplicate Username Registration

**Description:** Verifies the system prevents duplicate username registration.  
**Pre-requisites:** Must follow **UAS001** (registration).  
**Steps:**

1. Navigate to `http://localhost:5173/register/admin`.
2. Enter `correctUsername` in the **Username** field.
3. Enter `correctPassword` in the **Password** field.
4. Click the **Submit** button.
5. Wait for the page to load and observe the URL.  
   **Expected Outcome:** The user remains on `http://localhost:5173/register/admin` with an appropriate error message.

---

### 3.4 User015: Invalid Username Login

**Description:** Verifies the system prevents login with an invalid username.  
**Pre-requisites:** None
**Steps:**

1. Navigate to `http://localhost:5173/login`.
2. Enter `wrongUsername` in the **Username** field.
3. Enter `correctPassword` in the **Password** field.
4. Click the **Submit** button.
5. Wait for the page to load and observe the URL.  
   **Expected Outcome:** The user remains on `http://localhost:5173/login` with an appropriate error message.

---

### 3.5 User016: Invalid Password Login

**Description:** Verifies the system prevents login with an invalid password.  
**Pre-requisites:** None  
**Steps:**

1. Navigate to `http://localhost:5173/login`.
2. Enter `correctUsername` in the **Username** field.
3. Enter `wrongPassword` in the **Password** field.
4. Click the **Submit** button.
5. Wait for the page to load and observe the URL.  
   **Expected Outcome:** The user remains on `http://localhost:5173/login` with an appropriate error message.

---

### 3.6 User017: Missing Username Login

**Description:** Verifies the system prevents login if username is missing.  
**Pre-requisites:** None 
**Steps:**

1. Navigate to `http://localhost:5173/login`.
2. Leave the **Username** field empty and enter `somePassword` in the **Password** field.
3. Click the **Submit** button.
4. Wait for the page to load and observe the URL.  
   **Expected Outcome:** The user remains on `http://localhost:5173/login` with an appropriate error message.

---

### 3.7 User018: Missing Password Login

**Description:** Verifies the system prevents login if password is missing.  
**Pre-requisites:** Must follow **User001** (registration).  
**Steps:**

1. Navigate to `http://localhost:5173/login`.
2. Leave the **Password** field empty and enter `someUsername` in the **Username** field.
3. Click the **Submit** button.
4. Wait for the page to load and observe the URL.  
   **Expected Outcome:** The user remains on `http://localhost:5173/login` with an appropriate error message.

---

### 3.8 User019: Missing Username Registration

**Description:** Verifies the system prevents registration if username is missing.  
**Pre-requisites:** None.  
**Steps:**

1. Navigate to `http://localhost:5173/register/admin`.
2. Leave the **Username** field empty and enter `password` in the **Password** field.
3. Click the **Submit** button.
4. Wait for the page to load and observe the URL.  
   **Expected Outcome:** The user remains on `http://localhost:5173/register/admin` with an appropriate error message.

---

### 3.9 User020: Missing Password Registration

**Description:** Verifies the system prevents registration password is missing.  
**Pre-requisites:** None.  
**Steps:**

1. Navigate to `http://localhost:5173/register/admin`.
2. Leave the **Password** field empty and enter `username` in the **Username** field.
3. Click the **Submit** button.
4. Wait for the page to load and observe the URL.  
   **Expected Outcome:** The user remains on `http://localhost:5173/register/admin` with an appropriate error message.

### 3.10 Image001: Test Load And Write JPG From File System

**Description:** Verifies that a JPG file can be loaded from the file system and saved as a PNG.
**Pre-requisites:** The file `../../resources/images/test/input/test_image_1.jpg` must exist.  
**Steps:**

1. Navigate to `http://localhost:5173/` in your web browser
2. Click **"Choose File"** and browse for the required image.
3. Click **"Upload New Image"**
     **Expected Outcome:**
- The image loads successfully and is visible on the reloaded webpage without errors.
- The image is saved in PNG format without errors.

---

### 3.11 Image002: Test Load And Write PNG From File System

**Description:** Verifies that a PNG file can be loaded from the file system and saved as a PNG.  
**Pre-requisites:** The file `../../resources/images/test/input/test_image_2.png` must exist.  
**Steps:**

1. Navigate to `http://localhost:5173/` in your web browser
2. Click **"Choose File"** and browse for the required image.
3. Click **"Upload New Image"**
     **Expected Outcome:**
- The image loads successfully and is visible on the reloaded webpage without errors.
- The image is saved in PNG format without errors.

---

### 3.12 Image005: Test Image Embedding And Retrieval

**Description:** Verifies that data can be embedded into an image and retrieved correctly.  
**Pre-requisites:** The file `../../resources/images/test/input/test_image_7.png` must exist. The tester must have two valid usernames and passwords login to the private website.
**Steps:**

1. Navigate to `http://localhost:5173/login`
2. Enter the first valid username and password and login.
3. Click **"Choose File"** and browse for the required image.
4. Enter the message "Hello world"
5. Upload the image and copy the key provided.
7. Logout
8. Login with the second valid username and password.
9. Enter your key from step 5 and confirm the corresponding message is "Hello world."
     **Expected Outcome:**
- The correct message is displayed.

---

## 4.0 Automated Testing

### 4.1 Backend Automated Testing

On the backend we are using the Boost testing library to facilitate automated testings.

---

**Setup Actions:**

1. **Install Dependencies**  
   Ensure you have `Boost.Test` and all necessary libraries installed.

   ```
   sudo apt-get install libboost-test-dev
   ```

2. **Navigate to the backend project directory**  
   Open the terminal and navigate to the project directory:

   ```
   cd apps/backend
   ```

3. **Build the test suite**  
   Use the `make` command to compile the test files:

   ```
   make test
   ```

4. **Run the test suite**  
   Execute the compiled test binary:
   ```
   ./bin/test/HiddenFrame_Test
   ```

### 4.2 Frontend Automated Testing

This section provides detailed information on the Playwright script used to automate the user acceptance test process for **HiddenFrame** UI. The script is designed to validate the full end-to-end functionality of the application, ensuring seamless integration of its core features.

**Setup Actions:**

1. **Run the backend**
   Open the terminal and enter
   ```bash
   cd apps/background
   make run
   ```
2. **Run the frontend**

   Open another terminal and enter

   ```bash
   cd apps/web
   npm i
   npm run dev
   ```

3. **Start the playwright**

   Open another terminal and enter

   ```bash
   cd apps/web
   npm install -D @playwright/test@latest
   npx playwright install --with-deps
   npm run test-debug
   ```

---

### 4.3. Full Cycle Tests

**Name and Location:**  
`apps/web/tests/full.cycle.spec.ts`

**Source Code and Build Location:**

- **Source Code:** [Full Cycle Test Source](../apps/web/tests/full.cycle.spec.ts)
- **Build Location:** [apps/web](../apps/web)

**Purpose:**  
This script automates the complete user flow for **HiddenFrame**, verifying the following key functionalities:

1. User registration with valid credentials.
2. User login with the registered credentials.
3. Image upload with an embedded message.
4. Decoding of the embedded message from the uploaded image.

---

#### 2. Login Tests

**Name and Location:**  
`apps/web/tests/login.spec.ts`

**Source Code and Build Location:**

- **Source Code:** [Login Test Source](../apps/web/tests/login.spec.ts)
- **Build Location:** [apps/web](../apps/web)

**Purpose:**  
This script validates the login process for the **HiddenFrame** application, ensuring correct functionality for the following scenarios:

1. Verifying that the page title is displayed correctly.
2. Checking if the login label is present on the login page.
3. Logging in successfully with valid credentials.
4. Preventing login with invalid usernames or passwords.
5. Handling scenarios where the username or password is missing.

---

### 4.4 Registration Tests

**Name and Location:**  
`apps/web/tests/register.spec.ts`

**Source Code and Build Location:**

- **Source Code:** [Register Test Source](../apps/web/tests/register.spec.ts)
- **Build Location:** [apps/web](../apps/web)

**Purpose:**  
This script validates the registration process for the **HiddenFrame** application, ensuring correct functionality for the following scenarios:

1. Verifying that the registration page title is displayed correctly.
2. Checking if the registration label is present on the page.
3. Preventing registration when a username already exists.
4. Preventing registration when required fields (username or password) are missing.

---

### 4.5 Main Page Tests

**Name and Location:**  
`apps/web/tests/main.spec.ts`

**Source Code and Build Location:**

- **Source Code:** [Main Page Test Source](../apps/web/tests/main.spec.ts)
- **Build Location:** [apps/web](../apps/web)

**Purpose:**  
This script validates the following functionalities on the **HiddenFrame** main page:

1. Verifying the page title.
2. Ensuring a public user can upload an image successfully.

## 5.0 Software Tools and Environment

ProjectHidden frame has been developed on, built, and tested by the development team using:
- Windows 11 running 5.15.167.4-microsoft-standard-WSL2 (debian);
- macOS 15.1.1; and
- libboost1.74-dev
- Playwright 10.9.0

### 5.1 Version Control and Branch Structure

The staging branch is used for testing. Automated tests are as detailed in the preceeding sections, we have written github workflows that run these tests on each PR to staging and master, hence almost every aspect is tested except the dev/custom branches.

### 5.2 Directory and File Structure and Content

Testing resources can be found in the following locations.  The fist expanded location contains the backend automated tests, the second expanded location contains the automated frontend tests, and the third expanded location contains input and output files that may be used for testing or are called in automated tests.

- project
   - apps
      - backend
         - bin
            - database
               - testuserdatabase.db
         - test
            - main.cpp
            - test_image_io.cpp
            - test_user_database.cpp
      - web
         - tests
            - full.cycle.spec.ts
            - login.spec.ts
            - main.spec.ts
            - register.spec.ts
         - test-examples
            - demo-todo-app.spec.ts
   - resources
      - images
         - test
            - input
               - test_image_1.jpg
               - test_image_2.png
               - test_image_3.png
               - test_image_4.png
            - output
               - test_image_1.png
               - test_image_2.png
               - test_image_7.png



### 5.3 Independent Subsystems and External Resources (Project Web/Database Servers)

Project HiddenFrame requires the following packages and dependencies and requires that the versions installed be at least what is listed or newer.
| Package  | Version |Use                                                                         |
| ------- | - |---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| Boost | 1.86.0_2 | Automated testing - required for testing and install |
| Playwrite | 1.47.0 | Automated testing - required for testing and install |
| Sqlite3 | 3.47.0 | User database - required for install |
| Node | 23.3.0 | Server framework - required for install |
| Asio | 1.30.2 | Connection handling - required for install |

Boost, Sqlite3, Node, and Asio can be installed using a package manager of your choice and running the executing the install keyword from a terminal.  For example, if using homebrew on macOS they may be installed by running the following command:

brew install boost sqlite3 node asio

or if using Advanced Package Tool in a Linux environment:

apt-get install boost sqlite3 node asio

See https://playwright.dev/docs/intro for more information on how to install playwrite.

<div style="page-break-after: always;"></div>

## 6.0 Appendix: Detailed Test Case Descriptions

## Test Case ID: User009 - Peformed in Playwrite

Description:

This test case ensures that a user can successfully register by entering valid credentials. The process includes navigating to the registration page, entering the correct username and password, submitting the form, and verifying the redirection to the login page.

[Requirement 4.2](../documentation/requirements.md#42-login-page) Login Requirement  

Pre-requisites:

Ensure that the server is running and accessible at http://localhost:5173.

1. Navigate to http://localhost:5173/register/admin.

2. Enter correctUsername in the Username field.

3. Enter correctPassword in the Password field.

Click the Submit button.
Wait for the page to load and observe the URL.
Expected Outcome: The user is redirected to http://localhost:5173/login.

Expected Results:

Registration form submission redirects the user to the login page without errors.

<div style="page-break-before: always;"></div>

## Test Case ID: User013 - Peformed in Playwrite

Description:

This test case checks that the user is able to log in successfully with valid credentials following a registration process. It ensures the login functionality works as expected.

[Requirement 4.2](../documentation/requirements.md#42-login-page) Login Requirement  

Pre-requisites:

This test follows User001 (successful registration).
The server should be running.

1. Navigate to http://localhost:5173/login.
2. Enter correctUsername in the Username field.
3. Enter correctPassword in the Password field.
4. Click the Submit button.
5. Wait for the page to load and observe the URL.
6. Expected Outcome: The user is redirected to http://localhost:5173.

Expected Results:
The user should be redirected to the homepage after successful login with the option to upload both a picture and a message.

<div style="page-break-before: always;"></div>

## Test Case ID: User014 - Peformed in Playwrite

Description: 

This test case checks that the system correctly prevents registration when a duplicate username is entered, ensuring that unique usernames are required for new registrations. It verifies the backend logic for handling duplicate usernames during the registration process.

[Requirement 4.2](../documentation/requirements.md#42-login-page) Login Requirement  

Pre-requisites:

This test follows User009 (successful registration).

Ensure that the server is running at http://localhost:5173.
A valid user (correctUsername) should already be registered prior to running this test.

Steps:

1. Navigate to http://localhost:5173/register/admin.
2. Enter correctUsername in the Username field (ensure this is the same username used during the registration in Usr009).
3. Enter correctPassword in the Password field.
4. Click the Submit button.
5. Wait for the page to load and observe the URL.
Expected Outcome:

The user remains on http://localhost:5173/register/admin, and an appropriate error message is displayed, indicating that the username is already taken and duplicate registrations are not allowed.

<div style="page-break-before: always;"></div>

## User015: Invalid Username Login - Peformed in Playwrite

Description: Verifies the system prevents login when an incorrect username is entered while the password is correct.
Pre-requisites: None

[Requirement 4.2](../documentation/requirements.md#42-login-page) Login Requirement                                              

Steps:

1. Navigate to http://localhost:5173/login.
2. Enter wrongUsername in the Username field.
3. Enter correctPassword in the Password field.
4. Click the Submit button.
Wait for the page to load and observe the URL.
Expected Outcome: The user remains on http://localhost:5173/login with an appropriate error message.

<div style="page-break-before: always;"></div>

## ImageI/O001: Test Load and Save JPG Image - Peformed in Playwrite

Description:
This test verifies that the application can successfully handle JPG image uploads and convert them to PNG format. It ensures compatibility with supported image formats and validates that the upload and saving process runs as expected.

[Requirement 3.2](../documentation/requirements.md#32-uploading-images) Uploading Images

Pre-requisites:

1. The file ../../resources/images/test/input/test_image_1.jpg must be present on the local file system.
2. The application server must be running and accessible at http://localhost:5173/.

Steps:
1. Open a web browser and navigate to http://localhost:5173/.
2. Click the "Choose File" button.
3. Select the file test_image_1.jpg from the specified directory.
4. Click the "Upload New Image" button to upload the selected file.

Expected Outcome:

The image is uploaded successfully and is displayed on the webpage without any errors.
The system converts the uploaded JPG file to PNG format and saves it.
The PNG file is accessible and retains the original image's visual fidelity.
Pass Criteria:
The test is considered successful if the uploaded image is displayed correctly on the webpage, the file is saved in PNG format, and no errors occur during the process.

<div style="page-break-before: always;"></div>

## ImageI/O002: Test Load and Save PNG Image - Peformed in Playwrite

Description:

This test verifies that the application can successfully handle PNG image uploads. It ensures compatibility with supported image formats and validates that the upload and saving process runs as expected.

[Requirement 3.2](../documentation/requirements.md#32-uploading-images) Uploading Images

Pre-requisites:

1. The file ../../resources/images/test/input/test_image_1.png must be present on the local file system.
2. The application server must be running and accessible at http://localhost:5173/.

Steps:

1. Open a web browser and navigate to http://localhost:5173/.
2. Click the "Choose File" button.
3. Select the file test_image_1.png from the specified directory.
4. Click the "Upload New Image" button to upload the selected file.

Expected Outcome:

The image is uploaded successfully and is displayed on the webpage without any errors.
The PNG file is accessible and retains the original image's visual fidelity.
Pass Criteria:
The test is considered successful if the uploaded image is displayed correctly on the webpage, the file is saved in PNG format, and no errors occur during the process.

<div style="page-break-before: always;"></div>

## ImageI/O005: Test Image Embedding and Retrieval - Peformed in Playwrite

Description:
This test verifies the system's ability to embed a secret message into an image and accurately retrieve it. The process ensures that the image remains visually unchanged while securely storing the embedded data, demonstrating compliance with the feature requirements.

[Requirement 3.2](../documentation/requirements.md#32-uploading-images) Uploading Images

Pre-requisites:

The file ../../resources/images/test/input/test_image_7.png must be available on the local file system.
Two valid user accounts with distinct usernames and passwords must exist.
The application server must be running and accessible at http://localhost:5173/.

Steps:

1. Open a web browser and navigate to http://localhost:5173/login.
2. Log in using the first valid username and password.
3. Click the "Choose File" button and select test_image_7.png from the local file system.
4. Enter the message "Hello world" into the text field provided for embedding.
5. Click the "Upload New Image" button.
6. Copy the unique key generated for retrieving the embedded message.
7. Log out from the current account.
8. Log in using the second valid username and password.
9. Enter the copied key from step 6 into the retrieval field.
10. Confirm that the retrieved message matches "Hello world".

Expected Outcome:

- The image is successfully uploaded and the message "Hello world" is embedded with minimal alteration to the visual quality of the image.
- A unique key is generated and displayed for future retrieval.
- Upon entering the key, the system retrieves and displays the exact message "Hello world" without errors.
