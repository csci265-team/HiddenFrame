
# CSCI 265 Initial Project Proposal

## Team name: HiddenFrame Project

## Project/product name: HiddenFrame

## Contact person and email address

Patrick Candy - candy.pat@gmail.com

## Project Overview

Project HiddenFrame is, in brief, a picture board (like Pinterest) that will use various technologies like DBMS, WebRTC, and APIs. It also acts as a secret message board by using stenography. HiddenFrame will be publicly accessible and encourage the general public to share photographic content; meanwhile, select users will be using HiddenFrame's true capabilities to exchange pictures encoded with hidden data. (Which only a select few will know about)

HiddenFrame will achieve its purpose by first providing an attractive social media experience to attract as many users as possible and thereby provide better obscurification for the secret messages. The secret messages section of the site will be access-controlled and allow users to communicate covertly.

## Target audience and motivation

HiddenFrame is intended to obfuscate hidden messages. The project has an application wherever the passage of data must go unremarked. In particular, this project has applications in journalism and policing, both situations where communication from sources covertly is important. Additionally, the project has potential uses in PEN testing.

Our team discussed a very diverse set of possible projects. We ultimately settled on this one because we felt that it had a great deal of variety. It will involve networking, web design, image manipulation, and encryption (at a minimum). The hope is that this project will allow each team member to grow as a developer. 

## Key features and discussion

### Social Site

The project will use a social media site to camouflage its true purpose. Nonetheless, the social media aspect needs to be attractive and user-friendly in order to elicit widespread use. The primary features we hope to provide are:
- Image upload and download to servers
- WebGUI with a privileged section for secret sharing.

### Secret Messages

The other purpose of the project will be to create a program that: 
- accepts an image as its input 
- processes the image in such a way that the image is unremarkably different to a human, but now contains some data payload within the image.
- process a carrier image to retrieve the original payload. 

## Preliminary interface sketches

### Public View
We aim to provide a website with a streamlined aesthetic similar to Pinterest or Imgur. Both websites employ a splash page of popular photos in a 'card' format. We plan to develop a similar layout.
![Public View](./resources/images/HiddenFrame%20Public%20View.png)

### Private View
We also intend to have a private view that retrieves the payload from images. The images that do not contain a payload should remain unmodified. 

![Private View](./resources/images/HiddenFrame%20Private%20View.png)

## Scaling plans

If the project needs to be scaled down, we will either: 
- focus on producing a program that successfully completes the steganographic process without the picture board site.
- focus on producing a picture-sharing site without the steganographic features.

Ideas for scaling up include: 
- supporting additional input/output file types, e.g. seeding a picture with audio payload instead of text or seeding an audio file with the payload. 
- getting the project/AI to generate images instead of being provided with an image to seed.
- End-to-end encryption of the message. 
- Single-read messages.
- Spread Payload across multiple carriers. 


## Risks and potential issues

The team does not, overall, have a strong foundation in website creation. Since a 'social media site' is a large portion of the functionality of this project, this knowledge gap could be a potential problem. 

As with many security/privacy tools, this project has the potential to be abused by malicious actors. 
