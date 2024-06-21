<!-- PROJECT LOGO -->
<br />
<div align="center">
    <img src="https://github.com/benammarfares/Charging_Station_App/assets/99650831/5b4d9eb4-6c07-4305-9dc5-c76b6e5dadec" alt="Logo" width="80" height="80">


  <h3 align="center">Chargi App</h3>

  <p align="center">
      Chargi is a Desktop Application for 'Electric Station management' .
    <br />
    <a href="https://github.com/benammarfares/Charging_Station_App"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/benammarfares/Charging_Station_App">View Demo</a>
    ·
    <a href="https://github.com/benammarfares/Charging_Station_App/issues/new?labels=bug&template=bug-report---.md">Report Bug</a>
    ·
    <a href="https://github.com/benammarfares/Charging_Station_App/issues/new?labels=enhancement&template=feature-request---.md">Request Feature</a>
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project
![Capture2](https://github.com/benammarfares/Charging_Station_App/assets/99650831/07c6dd1b-c576-4431-9eff-ea8c70503374)
<br>
* This project currently has only one branch, which was created and made in 2023 on the University Branch. I have decided to make it public for anyone who wants to add to or upgrade the work. For any other information about it, please feel 
  free to contact me.

  * As I mentioned, this is a desktop application project that also has a prototype of a solar panel, RFID, and LCD authentication using an Arduino Uno board. However, the project can work without the Arduino configuration if needed.

  * Like any desktop application, there are admin, staff, and client user roles. Each user has their own login and interface to manage the system. Clients can add their car details (model, date, battery level, battery capacity, etc.) so they       can charge their electric cars at the station.

  * The car information is related to a session table, where the car will be charged with electricity. That table will primarily track the session capacity to charge cars at the station.

  * Additionally, each client will have a profile interface to easily manipulate their account without having to come to the station every time they want to change something.

  * The system also includes maintenance of the charging sessions, so that when a session is empty, it can be recharged.

  * In the prototype, I have included a solar panel that tracks any available light and generates voltage based on the light levels. This voltage is used to charge the sessions, with the solar panel working in the morning and at night when it 
    is loaded.

  * Furthermore, I have implemented a client authentication system using a card and RFID, so each client can use their card to identify themselves and then charge their car. While the client is charging, they can see the real-time charging 
    process percentage displayed on an LCD. Once the car is fully charged, a buzzer will sound as an alarm, and a motor will lift the stop panel next to the car.

    
<p align="right">(<a href="#readme-top">back to top</a>)</p>



### Built With

For database i used Oracle sql developer :<br>

* ![Qt](https://img.shields.io/badge/Qt-%23217346.svg?style=for-the-badge&logo=Qt&logoColor=white)
* ![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
* ![Oracle](https://img.shields.io/badge/Oracle-F80000?style=for-the-badge&logo=oracle&logoColor=white)

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- GETTING STARTED -->
## Getting Started

This is an example of how you may give instructions on setting up your project locally.
To get a local copy up and running follow these simple example steps.

### Prerequisites

This is an example of how to list things you need to use the software and how to install them.


 *https://drive.google.com/file/d/1inQFrlNt02O20WLUKkXcipZpEiOygubH/view?usp=drive_link<br>
 *https://drive.google.com/file/d/12Vful6RhPNxS-lWOpdJFL1ozW5DmJmEC/view?usp=drive_link<br>
 *https://drive.google.com/file/d/1abS1tQ0mxIGWu42R1-JL-oLfciTWCVHE/view?usp=drive_link<br>
 *https://drive.google.com/file/d/1Xw_kS7YtXPdF6kPMcE337L_jNwAwYFlb/view?usp=drive_link<br>


### Installation

_Below is an example of how you can instruct your audience on installing and setting up your app. This template doesn't rely on any external dependencies or services._

1. Clone the repo
   ```sh
   git clone https://github.com/benammarfares/Charging_Station_App.git
   ```
2. Install Oracle environment
 * https://drive.google.com/file/d/12Vful6RhPNxS-lWOpdJFL1ozW5DmJmEC/view?usp=drive_link<br>
 
3.Install Sql developer
 * https://drive.google.com/file/d/1inQFrlNt02O20WLUKkXcipZpEiOygubH/view?usp=drive_link<br>

4.Install Odbc Configuration
 * https://drive.google.com/file/d/1abS1tQ0mxIGWu42R1-JL-oLfciTWCVHE/view?usp=drive_link<br>
 * https://drive.google.com/file/d/1Xw_kS7YtXPdF6kPMcE337L_jNwAwYFlb/view?usp=drive_link<br>
   
<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- USAGE EXAMPLES -->
## Usage

Use this space to show useful examples of how a project can be used. Additional screenshots, code examples and demos work well in this space. You may also link to more resources.

_For more examples, please refer to the [Documentation](https://example.com)_

<p align="right">(<a href="#readme-top">back to top</a>)</p>







