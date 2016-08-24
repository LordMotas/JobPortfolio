--Project Euler #25
--What is the index of the first term in the Fibonacci
--sequence to contain 1000 digits?

with Ada.Text_IO; use Ada.Text_IO;
with Ada.Numerics.Elementary_Functions; use Ada.Numerics.Elementary_Functions;

procedure Euler25 is

  package IO renames Ada.Text_IO;
  package Math renames Ada.Numerics.Elementary_Functions;
  
  --Variable Declarations
  Answer : Float;

begin

  --Use the golden ratio inequality to solve
  Answer := (Math.Log(10.0)*999.0 + (Math.Log(5.0)/2.0))/Math.Log(1.6180);

  IO.Put_Line("The answer is: "&Integer'Image(Integer(Answer)));
  
end Euler25;