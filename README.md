
<a  align="center" name="readme-top"></a>

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
    <li><a href="#contributing">Contributing</a></li>
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

For database We used Oracle sql developer :<br>

* ![Qt](https://img.shields.io/badge/Qt-%23217346.svg?style=for-the-badge&logo=Qt&logoColor=white)
* ![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
* ![Oracle](https://img.shields.io/badge/Oracle-F80000?style=for-the-badge&logo=oracle&logoColor=white)

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- GETTING STARTED -->
## Getting Started

❗❗❗ Important !!! <br>
 *After cloning you must change the export.sql , don't worry it's a simple modification. (Just change FARES1 with your ODBC Client Username, this Username also should be the one for your DB ,for more informations watch the video i linked it covers all the configuration parts 😉)
The most important thing is that you should create the db in Oracle Sqldeveloper (also in the video 😅).
And for the database config just open connexion.cpp for any modification based on your requirements.
 

### Prerequisites

Follow the youtube Video to establish the Oracle Connexion with Qt.

* [Youtube Video How to setup Oracle Conection Qt](https://www.youtube.com/watch?v=E81Z5hCMCYg&t=1201s)

     *[Oracle 11](https://drive.google.com/file/d/12Vful6RhPNxS-lWOpdJFL1ozW5DmJmEC/view?usp=drive_link)<br>
     *[Sql developer](https://drive.google.com/file/d/1inQFrlNt02O20WLUKkXcipZpEiOygubH/view?usp=drive_link)<br>
     *[Instant Client odbc](https://drive.google.com/file/d/1abS1tQ0mxIGWu42R1-JL-oLfciTWCVHE/view?usp=drive_link)<br>
     *[Instant Client basic](https://drive.google.com/file/d/1Xw_kS7YtXPdF6kPMcE337L_jNwAwYFlb/view?usp=drive_link)<br>


### Installation

1. Clone the repo
   ```sh
   git clone https://github.com/benammarfares/Charging_Station_App.git
   ```
2. Install Oracle environment & watch the youtube video for more instructions about configurations.
 * [Oracle 11](https://drive.google.com/file/d/12Vful6RhPNxS-lWOpdJFL1ozW5DmJmEC/view?usp=drive_link)<br>
 
3. Install Sql developer & watch the youtube video for more instructions about configurations.
 * [Sql developer](https://drive.google.com/file/d/1inQFrlNt02O20WLUKkXcipZpEiOygubH/view?usp=drive_link)<br>

4. Install Odbc Configuration<br>
 * [Instant Client odbc](https://drive.google.com/file/d/1abS1tQ0mxIGWu42R1-JL-oLfciTWCVHE/view?usp=drive_link)<br>
 * [Instant Client basic](https://drive.google.com/file/d/1Xw_kS7YtXPdF6kPMcE337L_jNwAwYFlb/view?usp=drive_link)<br>
   
<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- USAGE EXAMPLES -->
## Usage

1. At first open integration.pro.
   
![cap1](https://github.com/benammarfares/Charging_Station_App/assets/99650831/07bcc8b1-a558-4532-918a-29f0d9c0306e)

2. Second open connexion.cpp and change the username and mdp same as the one you connect with to your sql developer Bd.
   
![cap2](https://github.com/benammarfares/Charging_Station_App/assets/99650831/900a8776-309e-49cb-bfc5-6dce21ee5908)
    
3. Third Step click on execute button.

![cap3](https://github.com/benammarfares/Charging_Station_App/assets/99650831/fcc6cc2a-0d1b-45a2-bbd8-fa37541e5569)
    

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- CONTACT -->
## Contact

 <a href="https://www.linkedin.com/in/fares-ben-ammar-14b8b3226/">
                <img alt="LinkedIn" title="Discord" src="https://img.shields.io/badge/linkedin-%230077B5.svg?style=for-the-badge&logo=linkedin&logoColor=white"/></a> 
    <a href="https://www.instagram.com/fares.ben.ammar/?hl=fr">
                <img alt="Instagram" title="Instagram" src="https://img.shields.io/badge/Instagram-%23E4405F.svg?style=for-the-badge&logo=Instagram&logoColor=white"/></a>
        <a href="https://discord.gg/farou1747">
                    <img alt="Discord" title="Discord" src="https://img.shields.io/badge/Discord-%235865F2.svg?style=for-the-badge&logo=discord&logoColor=white"/></a> 
            <a href="https://facebook.com/https://www.facebook.com/faroutiti.benammar/">
                    <img alt="Facebook" title="Facebook" src="https://img.shields.io/badge/Facebook-%231877F2.svg?style=for-the-badge&logo=Facebook&logoColor=white"/></a> 
    <a href="mailto:benammar.Fares@esprit.tn">
    <img alt="Outlook" title="Outlook" src="https://img.shields.io/badge/Microsoft_Outlook-0078D4?style=for-the-badge&logo=microsoft-outlook&logoColor=white"/>



<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

Important to who will start from scratch !!!! :)

* [Youtube Video How to setup Oracle Conection Qt](https://www.youtube.com/watch?v=E81Z5hCMCYg&t=1201s)
* [Git Operations](https://drive.google.com/file/d/108UbY6Nzs83a4eAT98fKQeBSKKNvyANo/view?usp=drive_link)
* [Urls for Qt Starting tutorials](https://drive.google.com/file/d/1-qULdcW115N1C3EVpoL2eL9nRYnWPR1K/view?usp=drive_link)
<p align="right">(<a href="#readme-top">back to top</a>)</p>





