# CSCI 265 User Acceptance Testing (Phase 5)

## Team name: Team HiddenFrame

## Project/product name: HiddenFrame

## Known Issues

This is likely to be a large and highly detailed document, describing many scripts, files, and other resources on the team repo (and possibly elsewhere). It is likely that the team will not have the time to fully complete all the various repo-side test content, so the known issues section should clearly and precisely identify what is incomplete (along with any other known errors/omissions in the document).

## The Test Plan

This section should provide the user with a full understanding of the process to be followed: starting with an overview of the process and an introduction to the key anticipated challenges, then laying out the intended timeline, the roles and responsibilities for the different testers, the process to be followed in detail, and a summary of all the test cases to be applied. (The full detailed description of each test case can then be included in a document appendix.)

### Testing Overview

This section needs to provide a general description of the testing environment, process, test cases, challenges, and timeline for the user acceptance testing of your project. In essence it summarizes the most important points of each of the other sections of the document and gives the reader the needed background/context/organizational structure before reading the various (more detailed) later sections.

### Key Front-End Testing Challenges

In this section the objective is to give the reader a clear understanding of the biggest challenges/obstacles in the thorough testing of all the requirements for your product. (The challenges faced will be very particular to the specific product and its runtime environment.)

### Key Back-End Testing Challenges

In this section the objective is to give the reader a clear understanding of the biggest challenges/obstacles in the thorough testing of all the requirements for your product. (The challenges faced will be very particular to the specific product and its runtime environment.)

### Testing Timeline

This will be a purely hypothetical exercise that assumes the core product/features are completed by Dec. 6th and that each member of the team has about 10 hours per week available for the project testing after Dec. 6th.
Based on those assumptions, provide a short timeline that covers
the completion of each unfinished part of the test infrastructure (scripts, data files, etc),
the completion of each unfinished part of the test documentation (e.g. the test case appendices),
one complete run of every test case and all the associated reporting.
For each aspect, be sure the timeline notes which team member will be carrying out the task.

### Test Process

The intent of this section is to ensure the reader understands the process the testers will follow with each of the different types of test. This section should provide an overview of
the general roles/responsibilities of the testers,
the general test environment, tools, and infrastructure used,
the typical setup process prior to running a test case,
the typical process for running a test case,
the typical process for evaluating and reporting on a test case,
any details needed to ensure the test process adheres to the version control process laid out in the team standards.
This is essentially a high level/intuitive summary of the remaining sections of the document.

### Test Cases Summary and Organization

This section should describe the core different types of test case relevant to your product and how the test cases have been organized. As an example, a breakdown might be something like:
tests involving visual inspections of the screen elements,
tests involving navigation between different parts of the system,
tests involving interactions with the database,
tests involving interactions with the AI,
testing of the map structure,
testing of NPC behaviour,
testing of combat mechanics,
etc etc etc.
Since this is specifically for user acceptance testing, the organization of your test cases should make it very easy for a reader to confirm that every aspect of the requirements document is indeed covered by these tests. One suggestion would be to organize the test cases to parallel the structure of the requirements document (so you could have the two documents open side-by-side and as you read through the requirements sections you could see the matching tests in the test document), while another might be to provide an additional field in the list/table below to identify which (sub/subsub)section of the requirements is addressed by each test case.

### Test Case List

A table or list of all the test cases to be applied, organized into intuitive sections/subsections, with each entry providing the test case id/name (linked to its detailed description in the appendix), and a few words clarifying the unique purpose/aspect of the test case.
A couple of sample entries might be something like the following (links not represented here):
PwdInv01	First bad password	one entry of bad password by registered user
PwdInv03	Third password failure	third consecutive bad password by registered user

#### Key Generation Testing
| Test # | Description|
|--------| ----------------------------------------------------------- | 
| Keys001 |  Generating a dummy key. This should generate a dummy key that looks like a typical key but does NOT match a valid key's requirements. |
| Keys002 | Generating a key for an image/message with more than the maximum number of characters.  Should return a throw error. |
| Keys003 | Generating a key for a message with the minimum number of characters. Should return a valid key. |
| Keys004 | Generating a key for a message with the maximum number of characters. Should return a valid key. |
| Keys005 | Generating two keys for identical images and messages.  Should generate unique valid keys for both carriers/payloads. |
| Keys006 | Generating 500 random image sizes and 500 random text string sizes to calculate the average time for each key generation. Generating the image sizes and text string sizes should not be included in the average time calculation. NEED TO DECIDE WHAT AN ACCEPTABLE TIME THRESHOLD SHOULD BE TO GENERATE A KEY AND/OR EMBED AN IMAGE. |
| Keys007 | Generating a key for an image that does not exist. Should return a throw error. |
| Keys008 | Generating a key for an image that is greater than the maximum allowed image size ((2^31)+1 pixels). Should return a throw error. |
| Keys009 | Generating a key for an image that is of the minimum size (3 pixels for a 4 channel image, with one 8-bit character of all 0s or all 1s, plus the stopping pixel). Should generate a valid key. |
| Keys010 | Generating a key for an image that is the minimum size (4 pixels for a 3-channel image, with one 8-bit character of all 0s or all 1s, plus the stopping pixel). Should generate a valid key. |
| Keys011 | Generating a key for an image that is the minimum size (9 pixels for a 2-channel image, with one 8-bit character of any pattern, plus the stopping pixel). Should generate a valid key. |
| Keys012 | Generating a key for an image that is the minimum size (9 pixels for a 1-channel image, with one 8-bit character of any pattern, plus the stopping pixel). Should generate a valid key. |
| Keys013 | Generating a key for an image that is of the maximum pixel size (largest 32-bit integer (2^31)) for any valid character length. Should generate a valid key. |
| User001 | Create an invalid username with more than one "@" characters. Username should not be created. |
| User002 | Create an invalid username with more than one "." characters after the singular "@" character. Username should not be created. |
| User003 | Create an invalid username where the first character in the username is an "@" character (ie no user before the @domain). Username should not be created. |
| User004 | Create an invalid username with no "@" character (ie no indication of where the @domain begins). Username should not be created. |
| User005 | Create an invalid username with no "." after the singular "@" character (ie no indication of where .com .ca .other after the @domain begins). Username should not be created. |
| User006 | Create an invalid username with no "a-z" characters between the singular "@" and singular trailing "." characters (no domain in @domain). Username should not be created. |
| User007 | Create an invalid username with no "a-z" characters after the singular "." character following the singular "@" character (ie no indication of .com .ca .other type). Username should not be created. |
| User008 | Create a special character (!@#$%^&*()_-+=) appears after the "." character following the singular "@" character. Username should not be created. |
| User009 | Create a valid user account using an email address. User should be added. |
| User010 | Create five valid user accounts from invites from the valid user account in User008 test. The five users should be added. |
| User011 | Attempt the creation of a sixth user account as an invite from a valid user account in User008 test. The sixth invite should not be created. |
| User012 | Create a new user account with a username matching an existing user account.  The user should not be created. |
| User013 | Create a new unique invite account from an existing invite account. The user account should be created. |
| User014 | Remove the inviter account from which the invitee was created for User013 test. Both the inviter and invitee should be removed. |
| User015 | Re-invite the inviter and invitee from User013 test. NEED TO DECIDE AS A GROUP IF THEY SHOULD BE REINVITED/REACTIVATED/ACCESS REVOKED/SENT TO ADMIN FOR APPROVAL. |

## Test Infrastructure

This section should outline everything needed in order to carry out the actual testing. The breakdown below provides a suggested structure, but (depending on the nature of your product and operating environment) you are welcome to organize it differently as long as equivalent/suitable information can all be quickly and easily found within the document by a first-time reader.

### Software Tools and Environment

The objective for this section is to describe the environment(s) in which you'll be running the product while testing and any additional tools you'll be using to conduct/monitor/report the test results.
This can vary considerably depending on the project/team, e.g.:
For a simple client-side game this might just specify whose laptop(s) and OS/version(s) you're testing on and that you're following manual 'user action scripts' as the process.
For a product that connects to other elements (AI, databases, web servers, etc) it will also need to specify which ones and how (this can be an overview, with details given in the 'External resources' section below).
If you're using third party tools (e.g. to record/playback UI actions) then those need to be listed and their use outlined here.

### User Action Scripts

To ensure test results are reproducible when carrying out manual user acceptance tests, we can prepare and follow 'user action scripts'. These can be thought of similarly to the script for a play: they detail precisely what actions each user/tester must take and when, with the assumption that during testing the tester will be reading through the script, performing the actions as described.
The scripts can be organized into logical sections (or scenes, if we're using a theatrical analogue), e.g. a script that just covers the registration process, a script that just covers the login process (and assumes a previous registration script has been followed), a script that just covers a user sending a message to another user (and assumes both users have been previously registered and the sender has already logged in).
For each script there should be (at least):
a unique id/name for the script
a short description/overview of the script
a list of which other scripts must have been 'run' (followed) prior to running this script (ideally linked to the descriptions of the other scripts)
the exact sequence of actions each tester must follow during the scene covered by the script
the expected behaviour/results and how to assess pass/failure
Note that the descriptions of the actions to be performed must be precise and detailed enough to guarantee we will get the same results if we run the same script in the future.

### Executables (Test Programs/Scripts, Stubs, and Drivers)

This section details any/all the scripts and programs the team has created to help automate the user acceptance test process. This would include programs/scripts such as:
those used to run specific test cases or batches of test cases,
stubs and drivers used to apply user acceptance tests to isolated portions of the system,
programs/scripts used in the process of setting up, evaluating, or cleaning up after different test cases (or sets of test cases),
any special-purpose scripts/programs related to the unique nature of an individual product.
For each script there should be (at least):
the name and location of the script/executable,
a link to the necessary source code and build location for executables,
a short description/overview of the purpose of the script/executable,
detailed descriptions (or links to such descriptions) for all the setup actions that need to be performed prior to running this script/executable,
the exact sequence of actions each tester must follow during execution of the script/executable,
the expected behaviour/results and how to assess pass/failure,
any required cleanup after the script has terminated.

### Version Control and Branch Structure

This section should clearly describe how the testing process fits with the teams version control standards and processes (i.e. what branches are used for testing, how they are set up/brought up to date immediately prior to testing).

### Directory and File Structure and Content

This section should clearly outline the directory structure and file organization for the project test content, providing things like:
an overview of what kinds of files are located where in the directory tree (action scripts, test executables and their sources, files containing test case input, files containing expected output, etc),
an overview of any naming conventions for the different kinds of files used: ideally names provide an indication of what kind of file it is (action script, stub, driver, test executable, user input data, expected output, etc) and what kind of testing it is used for (e.g. uix tests, navigation tests, etc).

### Independent Subsystems and External Resources (Project Web/Database Servers)

This section needs to provide full details on all the external resources the client side of the product relies upon/connects to, including things like
any AI components, web servers, and/or database servers run as part of the project,
any third party web servers and database servers that the product interacts with,
any third party AI components the product interacts with.
This section needs to provide all the details needed during testing to setup/run or connect to the relevant resources. These details can be provided in this document section or the document can link to later sections (appendices possibly?) where those details are provided in full.

### Appendix: Detailed Test Case Descriptions

For every test case listed in the earlier summary, this section should provide all the details about that case, typically with a one-page form for each test case. Depending on the nature of your product and the test case, this likely includes most of the following:
the test case id, name, one-line description,
an overview of the test covering both the specific purpose of this test case and the key steps involved in running the test case,
a link to the specific section of the requirements document that describes the portion/aspect/feature of the product that is being tested here,
how many testers are needed and what they are labelled as in the test case actions,
what scripts (action and/or executable) need to be run prior to running this test case and what (specific) arguments/options need to be used when running them, ideally with links to the scripts themselves,
exact details on all other settings/ actions that need to be performed prior to running the test case (e.g. what fixed seed is used by the pseudo-random number generator if the game/product makes use of any form of randomness), (these may link to files/documents detailing sets of actions that are used in multiple test cases),
what scripts (action and/or executable) need to be run to conduct this test case and what (specific) arguments/options need to be used when running them, ideally with links to the scripts themselves,
all expected results/output from the test case, in precise enough detail to allow pass/fail evaluation,
any cleanup scripts that need to be run or other actions that need to be taken to 'tidy up' following the test case (e.g. your test case might involve things like changing permissions or contents for specific files/directories/users: things you'll want to undo those following the test),
the reporting process to be followed: e.g. links to which forms are to be filled in, who to notify with pass/fail results, etc (this may be a link to one of several standard reporting processes the team has created for their project testing).