<p align="center">
    <h1 align="center">NOTIFICATIONS-SERVICE</h1>
</p>
<p align="center">
    <em><code>❯ REPLACE-ME</code></em>
</p>
<p align="center">
	<!-- Shields.io badges disabled, using skill icons. --></p>
<p align="center">
		<em>Built with the tools and technologies:</em>
</p>
<p align="center">
	<a href="https://skillicons.dev">
		<img src="https://skillicons.dev/icons?i=c,cpp,html,md&theme=light">
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

<code>❯ REPLACE-ME</code>

---

##  Features

<code>❯ REPLACE-ME</code>

---

##  Repository Structure

```sh
└── NotificationsService/
    ├── CMakeLists.txt
    ├── NotificationsService
    ├── README.MD
    ├── backend
    │   ├── auxiliary_functions
    │   ├── email_sender
    │   ├── multithread_notification_scheduler
    │   └── request_handler
    ├── interface
    │   └── index.html
    ├── main.cpp
    ├── openapi.yaml
    └── pg.sql
```

---

##  Modules

<details closed><summary>.</summary>

| File | Summary |
| --- | --- |
| [openapi.yaml](https://github.com/naziikk/NotificationsService/blob/main/openapi.yaml) | <code>❯ REPLACE-ME</code> |
| [NotificationsService](https://github.com/naziikk/NotificationsService/blob/main/NotificationsService) | <code>❯ REPLACE-ME</code> |
| [main.cpp](https://github.com/naziikk/NotificationsService/blob/main/main.cpp) | <code>❯ REPLACE-ME</code> |
| [pg.sql](https://github.com/naziikk/NotificationsService/blob/main/pg.sql) | <code>❯ REPLACE-ME</code> |
| [CMakeLists.txt](https://github.com/naziikk/NotificationsService/blob/main/CMakeLists.txt) | <code>❯ REPLACE-ME</code> |
| [README.MD](https://github.com/naziikk/NotificationsService/blob/main/README.MD) | <code>❯ REPLACE-ME</code> |

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

- [X] **`Task 1`**: <strike>Implement feature one.</strike>
- [ ] **`Task 2`**: Implement feature two.
- [ ] **`Task 3`**: Implement feature three.

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

##  License

This project is protected under the [SELECT-A-LICENSE](https://choosealicense.com/licenses) License. For more details, refer to the [LICENSE](https://choosealicense.com/licenses/) file.

---

##  Acknowledgments

- List any resources, contributors, inspiration, etc. here.

---