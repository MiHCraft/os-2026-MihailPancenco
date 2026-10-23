# os-2026-MihailPancenco
This is a repository for labs for UTM.

## Laboratory structure

Each lab keeps the teacher's PDF in `requirements/`, the requested deliverables in `submission/`, and its editable LaTeX sources plus compiled `main.pdf` in `report/`. Labs 01-03 are unchanged.

| Lab | Topic | Submission notes | PDF report |
| --- | --- | --- | --- |
| 04 | The xv6 Shell from the Outside | [notes.md](lab_04/submission/notes.md) | [Report](lab_04/report/main.pdf) |
| 05 | The File System with Your Own Hands | [report.md](lab_05/submission/report.md) | [Report](lab_05/report/main.pdf) |
| 06 | Inside the xv6 File System | [notes.md](lab_06/submission/notes.md) | [Report](lab_06/report/main.pdf) |
| 07 | Three Small Programs: Processes, Redirection, a Pipe | [report.md](lab_07/submission/report.md) | [Report](lab_07/report/main.pdf) |
| 08 | The Same Calls, Inside Your Own OS | [notes.md](lab_08/submission/notes.md) | [Report](lab_08/report/main.pdf) |

Reports use readable, selectable terminal listings instead of new screenshots. Captured transcripts are included in each submission. Environment-specific values are identified as measured in the Linux validation environment, rather than attributed to a separate Ubuntu laptop.

## Build instructions

For xv6 labs 04, 06 and 08, read the `README.md` in that lab's submission directory. The files under `submission/user/` are an overlay for an existing xv6-riscv checkout. Each submitted Makefile is a complete upstream Makefile with that lab's UPROGS entries; merge those entries into an already-customized checkout instead of overwriting earlier work.

For Linux lab 07:

```sh
cd lab_07/submission
make
./run
./run_date
./run_missing
./redirect
./pipeline
./pipeline3
make clean
```

For the Linux lab 05 experiments, run `bash lab_05/submission/collect.sh` as a non-root user on Linux. The script uses a fresh temporary directory and cleans it up on exit.

To rebuild any LaTeX report, run twice from its `report/` directory:

```sh
pdflatex -interaction=nonstopmode -halt-on-error main.tex
```

Keep the sibling `submission/` directory available: the source-code appendix imports the actual submitted C files. `main.tex` loads `body.tex`, `title_page.tex`, `conclusion.tex` and `bibliography.tex`. The PDF reports are already compiled.

See [VALIDATION.md](VALIDATION.md) for the recorded build and execution checks and environment limitations.
