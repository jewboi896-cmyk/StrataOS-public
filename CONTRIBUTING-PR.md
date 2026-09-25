## 🤝 Contribution & Pull Request Policy

Contributions are welcome, but given the solo nature of the project, please respect the following operational guidelines:

* **Review Latency**: Pull requests may sit unreviewed for extended periods (potentially years) during early infrastructure phases.

* **Scope Isolation**: Keep early PRs tightly focused on core **kernel-space code**. Do not touch user space until the
foundation has been formally scaffolded by me (the sole maintainer and dev).If you have user-space app ideas please open up a thread under the Discussions tab and I will get back to you on your idea as soon as I can.

* **Strict Build Consistency**: Do not submit PRs changing the core GNU Make structure unless you see that I have made a
mistake somewhere or you see that a optimization can be made to improve build times, have a smaller final binary size, etc.
You are also free to edit the linker for the same reasons as well. If you do so just open a PR and I will get back to you whenever I can.

* **Discussions**: If you have other ideas for user-space apps, please submit something in the discussions tab and tag me in it so that when I have time, I can take a look at it. Please keep this only regarding user-space stuff. If you spot a kernel bug or issue please open either a PR for bugs or a Issue for issues and I will take a look. Please hold off on submitting PRs or Issues at this stage while architectural planning is ongoing. General questions and design feedback in Discussions are highly welcome! Obviously, general discussions are also permitted like if you have questions or need advice on how to approach a problem, etc. 

* **Contributions**: Anybody can become a contributor regardless of number of commits or activity. Anybody is also free to reach out directly to me in the event that they want to become part of the core dev team. If you want to contact me privately, open an issue on my main page and I will get back to you as soon as I can. There will be no required time commitment for any potential core dev team members, you can build, test, and review anything at your own pace.

* **Notice**: All contributions and PRs must adhere to the AI.md policy. Failure to comply will result in a permanent ban on contributing. All contributions and PRs must sign off on every commit using: git commit -s. 
