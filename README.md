## Overview
We built a smart cushion that can classify sitting pressure patterns into different postures. When the cushion detects a bad sitting posture from the current user, it will notify the user by “buzzing” the cushion until the user changes the posture to a correct one. This design is aimed to adjust people’s sitting habits to reduce back pain or neck pain caused by bad sitting postures. Possibly, it might also be able to tell how long the users have been sitting.
## Statement of Problem
People are spending more and more time sitting down. Sitting while working is the norm in the knowledge industry. One study in 2018 shows that 25% of the US population spends more than 8 hours a day sitting down1. This is corroborated by interviews we’ve done, where interviewees reported estimates of 10-13 hours spent sitting in a typical day2. The problem with this trend is that long sitting times are linked to increased rates of many health problems, including muscle weakness in the legs and glutes, digestion issues, hip and back problems, cancers, heart disease, diabetes, blood clots, and stiff neck/shoulders/back3. There are also mental health issues linked with sitting for too long, like anxiety or depression3. Posture issues are deeply tied to sitting for long periods of time and have similar health impacts including incontinence, constipation, heartburn4, misaligned musculoskeletal system, wearing away of the spine, shoulder/neck/back pain, poor digestion, and breathing problems5. Other related issues include eye strain and damage from computer use, which is often what people are doing while sitting2.
From our interview process, we found that people are vaguely aware of the fact that they sit too long and have poor posture. They are vaguely aware of the health issues linked to these habits. But they do little to try and change this habits2.
## User Research
We design a survey and get over 300 responses,
Half of the users sit more than 6 hours,half of the people take a break or stand up every 2+ hours, half of the users are concerned about their sitting habits, more than 85% of the people concern bad sitting affect their health.
![user research](https://user-images.githubusercontent.com/20251285/61606186-e515d680-abfd-11e9-939b-501ae658f50c.png)
![user research2](https://user-images.githubusercontent.com/20251285/61606188-e515d680-abfd-11e9-8e34-4fdea60abe08.png)

Here is the link to our full survey result: https://docs.google.com/spreadsheets/d/19VHJsDAoxdRkpV4vnQF-0a0ltL_bWdiwvrCeV5GKE9M/edit#gid=793808212

## Software 
We use a FSR matrix to sense the force pressure and pass the data collected to the raspberry pi to do further data processing. The pre-trained machine learning model in the raspberry pi will recognize and data and predict the sitting postures. Meanwhile, the prediction will be uploaded to the firebase to show it to the front-end IOS app.
Software Diagram:

![software](https://user-images.githubusercontent.com/20251285/61606184-e47d4000-abfd-11e9-8214-3630c43a00fd.png)
APP UI:

![software](https://user-images.githubusercontent.com/20251285/61606192-e515d680-abfd-11e9-839d-6be9945412df.gif)

## Harware
We use 5 force sensitive resistors(FSR) to sense the sitting pressure and connect them to the PCB boards we designed that had shift registers, MUX, capacitors soldered on them. The PCB boards will then be connected to the arduino, so arduino can collect raw data. Aruino then will pass the data to the raspberry pi to do data processing. A buzzer connected to a power adapter will also be connected to the raspberry pi, so after the user has been sitting for a long time, it will buzz.

![software](https://user-images.githubusercontent.com/20251285/61606190-e515d680-abfd-11e9-94d8-d78efac94897.png)

Besides that, we designed several versions of the 3D models that best contain all the hardwares with minimum size.

![software](https://user-images.githubusercontent.com/20251285/61606198-f2cb5c00-abfd-11e9-83d2-a3675bc82830.png)
![software](https://user-images.githubusercontent.com/20251285/61606203-f5c64c80-abfd-11e9-8fd4-4ff361466377.png)





