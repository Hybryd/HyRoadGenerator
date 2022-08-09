
<a name="readme-top"></a>



<!-- PROJECT LOGO -->
<br />
<div align="center">
  

<h3 align="center">HyRoadGenerator</h3>

  <p align="center">
    Genereates polygons that simulate a 2D road network.
    
  </p>
</div>







<!-- ABOUT THE PROJECT -->
## About The Project


This is an implementation of an algorithm to generate a simple procedural polygonal road network.

The output can be displayed with gnuplot.

This was inspired by the following article: Rudzicz, Nicholas & Verbrugge, Clark. (2008). An iterated subdivision algorithm for procedural road plan generation. 4th International North-American Conference on Intelligent Games and Simulation, Game-On 'NA 2008. 

<p align="right">(<a href="#readme-top">back to top</a>)</p>



### Built With

* ![C++][C++]


<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- GETTING STARTED -->
## Getting Started

To get a local copy up and running follow these simple example steps.

### Prerequisites

This is an example of how to list things you need to use the software and how to install them.

* g++
  ```sh
  sudo apt-get install g++
  ```
* gnuplot
  ```sh
  sudo apt-get install gnuplot
  ```
* make
  ```sh
  sudo apt-get install make
  ```


<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Installation

1. Clone the repo
   ```sh
   git clone https://github.com/Hybryd/HyRoadGenerator.git
   ```
2. Go in the repo
    ```sh
    cd HyRoadGenerator
    ```
3. Run Makefile
   ```sh
   make
   ```

<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Usage

1. Run the program and redirect the output to a file
   ```sh
   ./main > polygons
   ```
2. Run gnuplot
   ```sh
   gnuplot
   ```
3. Use gnuplot to display the road network
  ```gnuplot
  > plot "./polygons" with lp lw 1 pt 0
  ```

<p align="right">(<a href="#readme-top">back to top</a>)</p>





<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->

[C++]: https://img.shields.io/badge/g++-9.4.0-blue.svg?style=flat&logo=g%2B%2B

