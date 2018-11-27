# IoT Pet Feeder

This project utilises a force sensor, SG90 servo, NRF52-DK board and thingsboard hosted on a laptop, with a connection to the board established over bluetooth.
The functionality includes:
* Weighing of the food bowl.
* Scheduled feeding times: breakfast, lunch and dinner.
* Scheduling fallback when the board loses connection to thingsboard.
* A servo controlled food release mechnism.
* Control of the release mechanism via thingsboard switches, on board button and scheduling.
* Functions for filling up the bowl until full.
* Change the feeding schedule via thingsboard.
* View weight history via thingsboard.

## Team Work:

The team was broken down into two teams:

* Hardware Team:
    * Dylan Walsh
    * Darragh Dunne

* BLE/Thingsboard team:
    * Joe O'Hara
    * Huy Vu

The project was broken down into smaller tasks, as seen in the [issues (closed) section](https://gitlab.scss.tcd.ie/cs7ns2-1819/team10/issues?scope=all&utf8=%E2%9C%93&state=closed.) of the gitlab repo.

Development was intially carried out individually by each team member, however towards the end of the project, team members utilised pair programming and mob programming techniques to combine features and complete the project.


## Authors

* **Huy Vu** 
* **Joe O'Hara** 
* **Darragh Dunne** 
* **Dylan Walsh** 

## Acknowledgments

* Jonathan Dukes for sample code and other IoT knowledge via discussions and lectures.

![alt text](https://gitlab.scss.tcd.ie/cs7ns2-1819/team10/raw/master/petFeeder.jpg)
