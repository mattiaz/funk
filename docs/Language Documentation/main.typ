#import "template.typ": *

#show: project.with(
  course: "TDP019 Projekt: Datorspråk",
  title: "Funk dokumentation",
  authors: (
    (name: "Mattias Ajander", email: "mataj513@student.liu.se"),
    (name: "Ludwig Moström", email: "ludmo578@student.liu.se"),
  ),
  date: "2025-04-20",
  term: "Vårterminen 2025",
  version: "1.0",
)

= Revisionshistorik
#table(
  columns: (5.5em, 1fr, 5.5em),
  inset: 4pt,
  stroke: 0.5pt,
  [*Version*], [*Description*], [*Date*],
  [0.1], [Utkast], [2025-04-20],
)

#pagebreak()

= Inledning
Inledning för att beskriva att detta är ett projekt på IP-programmet, i kursen TDP019 Projekt: datorspråk, som ni läser andra terminen, och en kort introduktion som beskriver vad det är för slags språk, som ni implementerat i detta projekt.

= Användarhandledning
Användarhandledning, där ni beskriver språket för den målgupp ni tänkte er, vilka konstruktioner som språket innehåller och exempel på hur de används. Gärna något större illustrativt exempel. Dokumentet skall ha en pedagogisk prägel och delar av denna kommer att speciellt granskas av läraren för UPG1 Kommunikation.

== Översikt

== Målgrupp

== Syntax och konstruktioner

== Exempel

= Systemdokumentation

== Systemöversikt
en översiktlig beskrivning av ert system

== Grammatik
grammatiken för språket

== Komponenter
vilka delar det består utav, t ex lexikalisk analys, parsing, översättning, evaluering

=== Lexer

=== Parser

=== Interpreter

== Klassöversikt
ev vilka klasser ni har och relation mellan dessa

== Representation
val av representation av t ex tokens, syntaxträd

== Algoritmer
använda algoritmer (med referens till tidigare kända) eller egen förklaring hur ni löst problement

== Kodstandard
har ni använt någon kodstandard, t ex för hur koden skrivs på rader och indentering, namn på identifierare etc.

== Installation & användning
packeteringen av kod för språket, eventuellt var man kan ladda in koden ifrån, installera den och använda språket

= Erfarenheter och reflektion

Ett avsnitt där ni redogör för de erfarenheter ni fått från detta projekt, vad gick lättare och vad var svårare än vad ni trodde. Jämförelse med er språkspecifikation från början, vad implementerade ni eller ej, vilka ändringar har ni genomfört relativt första planen. Använd er av språkdagboken som stöd för att komma ihåg vad som har hänt under projektet.

== Projektets gång

== Jämförelse med specifikation

== Reflektioner

#pagebreak()

= Bilagor

== Programkod

All programkod för språket går att hitta på #link("https://gitlab.liu.se/mataj513/tdp019/")[gitlab.liu.se/mataj513/tdp019/].

#pagebreak()

== BNF

#table(
  columns: (0.2fr, 0.8fr),
  align: (center, left),
  stroke: 0.5pt,
  [*Symbol*], [*Förklaring*],
  [`<...> | <...>`],[Eller],
  [`<...>*`],       [En eller flera],
  [`[ ... ]`],      [Frivillig],
  [`R'...'`],       [Regex]
)


#let bnf = read("../Language Specification/bnf.txt").split("\n").map(row => row.split("->").map(cell => cell.trim()))

#table(
  columns: 3,
  align: (left, center, left),
  gutter: 0pt,
  inset: 3pt,
  stroke: 0pt,
  ..for rule in bnf {
    if rule.len() == 2 {
      (raw(rule.at(0)), `::=`, raw(rule.at(1)))
    }
    else {
      if (rule.at(0).starts-with("|")) {
        ("", "   |", raw(rule.at(0).replace("| ", "", count: 1)))
      }
      else {
        ("","","")
      }
    }
  }
)
