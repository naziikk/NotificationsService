<p align="center">
    <h1 align="center">NOTIFICATIONS-SERVICE</h1>
</p>
<p align="center">
    <em>A service that will help you not to forget the important things.</em>
</p>
<p align="center">
	<!-- Shields.io badges disabled, using skill icons. --></p>
<p align="center">
		<em>Built with the tools and technologies:</em>
</p>
<p align="center">
	<a href="https://skillicons.dev">
		<img src="https://skillicons.dev/icons?i=cpp,html,js,docker,postgres&theme=light">
	</a></p>

<br>

#####  Table of Contents

- [ Overview](#-overview)
- [ Features](#-features)
- [ Repository Structure](#-repository-structure)
- [ Modules](#-modules)
- [ Getting Started](#-getting-started)
   - [ Prerequisites](#-prerequisites)
   - [ Installation](#-installation)
   - [ Usage](#-usage)
   - [ Tests](#-tests)
- [ Project Roadmap](#-project-roadmap)
- [ Contributing](#-contributing)
- [ License](#-license)
- [ Acknowledgments](#-acknowledgments)

---

##  Overview
**Notification-service** is a service that creates notifications with Yandex mail api integration.
You can schedule notifications for the near future and receive them by mail at the specified time. Everything works in multithreaded mode and you can view all functions of the application in openapi file. 

---

##  Features

- **Multi-threaded Notification Scheduler**: Schedule notifications that are processed in a multi-threaded environment, ensuring high performance and concurrency.

- **Email Integration**: Notifications can be sent via email, using the Yandex Mail API for seamless mail integration.

- **Token-Based Authentication**: Secure token-based authentication for all API requests, ensuring proper access control.

- **PostgreSQL Database Integration**: Store and manage notification data using PostgreSQL, providing reliability and performance for large datasets.

- **RESTful API**: Full API documentation via OpenAPI specification, offering endpoints for creating, updating, and deleting notifications.

- **Web Interface**: A user-friendly HTML interface to interact with the service and manage notifications directly from the browser.

- **Docker Support**: The service is fully containerized using Docker, simplifying deployment and scaling.

- **Error Handling and Logging**: Comprehensive error handling and logging mechanisms ensure service stability and troubleshooting.

- **Extensibility**: The system is designed with modular components, allowing easy integration of new features and services.

---


##  Repository Structure

```sh
└── NotificationsService/
    ├── CMakeLists.txt
    ├── Dockerfile
    ├── NotificationsService
    ├── README.MD
    ├── backend
    │   ├── auxiliary_functions
    │   │   ├── AuxiliaryFunctions.cpp
    │   │   └── AuxiliaryFunctions.h
    │   ├── email_sender
    │   │   ├── Email_sender.cpp
    │   │   └── Email_sender.h
    │   ├── multithread_notification_scheduler
    │   │   ├── Time_scheduler.cpp
    │   │   └── Time_scheduler.h
    │   └── request_handler
    │       ├── RequestHandler.cpp
    │       └── RequestHandler.h
    ├── docker-compose.yml
    ├── interface
    │   └── index.html
    ├── main.cpp
    ├── openapi.yaml
    └── postgres
        ├── PostgresProcessing.cpp
        ├── PostgresProcessing.h
        └── pg.sql
```

---

##  Modules

<details closed><summary>.</summary>

| File | Summary |
| --- | --- |
| [openapi.yaml](https://github.com/naziikk/NotificationsService/blob/main/openapi.yaml) | <code>❯ REPLACE-ME</code> |
| [docker-compose.yml](https://github.com/naziikk/NotificationsService/blob/main/docker-compose.yml) | <code>❯ REPLACE-ME</code> |
| [NotificationsService](https://github.com/naziikk/NotificationsService/blob/main/NotificationsService) | <code>❯ REPLACE-ME</code> |
| [main.cpp](https://github.com/naziikk/NotificationsService/blob/main/main.cpp) | <code>❯ REPLACE-ME</code> |
| [Dockerfile](https://github.com/naziikk/NotificationsService/blob/main/Dockerfile) | <code>❯ REPLACE-ME</code> |
| [CMakeLists.txt](https://github.com/naziikk/NotificationsService/blob/main/CMakeLists.txt) | <code>❯ REPLACE-ME</code> |
| [README.MD](https://github.com/naziikk/NotificationsService/blob/main/README.MD) | <code>❯ REPLACE-ME</code> |

</details>

<details closed><summary>postgres</summary>

| File | Summary |
| --- | --- |
| [pg.sql](https://github.com/naziikk/NotificationsService/blob/main/postgres/pg.sql) | <code>❯ REPLACE-ME</code> |
| [PostgresProcessing.h](https://github.com/naziikk/NotificationsService/blob/main/postgres/PostgresProcessing.h) | <code>❯ REPLACE-ME</code> |
| [PostgresProcessing.cpp](https://github.com/naziikk/NotificationsService/blob/main/postgres/PostgresProcessing.cpp) | <code>❯ REPLACE-ME</code> |

</details>

<details closed><summary>backend.request_handler</summary>

| File | Summary |
| --- | --- |
| [RequestHandler.h](https://github.com/naziikk/NotificationsService/blob/main/backend/request_handler/RequestHandler.h) | <code>❯ REPLACE-ME</code> |
| [RequestHandler.cpp](https://github.com/naziikk/NotificationsService/blob/main/backend/request_handler/RequestHandler.cpp) | <code>❯ REPLACE-ME</code> |

</details>

<details closed><summary>backend.multithread_notification_scheduler</summary>

| File | Summary |
| --- | --- |
| [Time_scheduler.h](https://github.com/naziikk/NotificationsService/blob/main/backend/multithread_notification_scheduler/Time_scheduler.h) | <code>❯ REPLACE-ME</code> |
| [Time_scheduler.cpp](https://github.com/naziikk/NotificationsService/blob/main/backend/multithread_notification_scheduler/Time_scheduler.cpp) | <code>❯ REPLACE-ME</code> |

</details>

<details closed><summary>backend.email_sender</summary>

| File | Summary |
| --- | --- |
| [Email_sender.h](https://github.com/naziikk/NotificationsService/blob/main/backend/email_sender/Email_sender.h) | <code>❯ REPLACE-ME</code> |
| [Email_sender.cpp](https://github.com/naziikk/NotificationsService/blob/main/backend/email_sender/Email_sender.cpp) | <code>❯ REPLACE-ME</code> |

</details>

<details closed><summary>backend.auxiliary_functions</summary>

| File | Summary |
| --- | --- |
| [AuxiliaryFunctions.h](https://github.com/naziikk/NotificationsService/blob/main/backend/auxiliary_functions/AuxiliaryFunctions.h) | <code>❯ REPLACE-ME</code> |
| [AuxiliaryFunctions.cpp](https://github.com/naziikk/NotificationsService/blob/main/backend/auxiliary_functions/AuxiliaryFunctions.cpp) | <code>❯ REPLACE-ME</code> |

</details>

<details closed><summary>interface</summary>

| File | Summary |
| --- | --- |
| [index.html](https://github.com/naziikk/NotificationsService/blob/main/interface/index.html) | <code>❯ REPLACE-ME</code> |

</details>

---

##  Getting Started

###  Prerequisites

**CPP**: `version x.y.z`

###  Installation

Build the project from source:

1. Clone the NotificationsService repository:
```sh
❯ git clone https://github.com/naziikk/NotificationsService
```

2. Navigate to the project directory:
```sh
❯ cd NotificationsService
```

3. Install the required dependencies:
```sh
❯ g++ -o myapp main.cpp
```

###  Usage

To run the project, execute the following command:

```sh
❯ ./myapp
```

###  Tests

Execute the test suite using the following command:

```sh
❯ googletest
```

---

##  Project Roadmap

- [X] **`Task 1`**: <strike>Implement multi-threaded notification scheduler</strike>
    - Create a notification scheduling system that supports multiple threads.
    - Ensure that the notifications are processed concurrently for efficiency.

- [X] **`Task 2`**: <strike>Integrate Yandex Mail API for email notifications</strike>
    - Add support for sending notifications via email using Yandex Mail API.
    - Ensure email delivery scheduling based on the notification time.

- [X] **`Task 3`**: <strike>Implement token-based authentication system</strike>
    - Create a system for generating and validating tokens.
    - Implement token-based access control for all API requests.
    - Add registration, token recovery, and authorization mechanisms.

- [X] **`Task 4`**: <strike>Develop web interface for managing notifications</strike>
    - Create an HTML-based interface for interacting with the notification service.
    - Implement a dashboard to view, create, and manage notifications.
    - Ensure seamless integration with the RESTful API.
  
- [X] **`Task 5`**: <strike>Optimize PostgreSQL database queries</strike>
    - Analyze and optimize SQL queries for performance improvements.
    - Add indexes where necessary and ensure efficient database schema design.

- [ ] **`Task 6`**: Add unit and integration tests
    - Implement unit tests for each module (scheduler, mail sender, etc.).
    - Add integration tests to validate the entire workflow, from creating notifications to sending emails.

- [ ] **`Task 7`**: Improve error handling and logging
    - Add comprehensive logging for debugging and monitoring purposes.
    - Implement robust error handling across the entire service.
  
- [ ] **`Task 8`**: Dockerize the application for easy deployment
    - Set up Docker for containerizing the service.
    - Ensure all dependencies are correctly included for smooth deployment.

---

##  Contributing

Contributions are welcome! Here are several ways you can contribute:

- **[Report Issues](https://github.com/naziikk/NotificationsService/issues)**: Submit bugs found or log feature requests for the `NotificationsService` project.
- **[Submit Pull Requests](https://github.com/naziikk/NotificationsService/blob/main/CONTRIBUTING.md)**: Review open PRs, and submit your own PRs.
- **[Join the Discussions](https://github.com/naziikk/NotificationsService/discussions)**: Share your insights, provide feedback, or ask questions.

<details closed>
<summary>Contributing Guidelines</summary>

1. **Fork the Repository**: Start by forking the project repository to your github account.
2. **Clone Locally**: Clone the forked repository to your local machine using a git client.
   ```sh
   git clone https://github.com/naziikk/NotificationsService
   ```
3. **Create a New Branch**: Always work on a new branch, giving it a descriptive name.
   ```sh
   git checkout -b new-feature-x
   ```
4. **Make Your Changes**: Develop and test your changes locally.
5. **Commit Your Changes**: Commit with a clear message describing your updates.
   ```sh
   git commit -m 'Implemented new feature x.'
   ```
6. **Push to github**: Push the changes to your forked repository.
   ```sh
   git push origin new-feature-x
   ```
7. **Submit a Pull Request**: Create a PR against the original project repository. Clearly describe the changes and their motivations.
8. **Review**: Once your PR is reviewed and approved, it will be merged into the main branch. Congratulations on your contribution!
</details>

<details closed>
<summary>Contributor Graph</summary>
<br>
<p align="left">
   <a href="https://github.com{/naziikk/NotificationsService/}graphs/contributors">
      <img src="https://contrib.rocks/image?repo=naziikk/NotificationsService">
   </a>
</p>
</details>

---

##  Acknowledgments

- List any resources, contributors, inspiration, etc. here.

---