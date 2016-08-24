--Project Euler #19
--How many Sundays fell on the first of the month during the twentieth century?

with Ada.Text_IO; use Ada.Text_IO;
with Ada.Calendar.Formatting; use Ada.Calendar.Formatting;

procedure Euler19 is

  package IO renames Ada.Text_IO;
  package Dates renames Ada.Calendar.Formatting;

  --Variable declarations
  answer : Integer := 0;
  
begin
  for Year in 1901..2000 loop
    for I in 1..12 loop
      if Day_Of_Week (Time_Of (Year, I, 1)) = Sunday then
        IO.Put_Line(Image(Time_Of(Year, I, 1)));
        answer := answer + 1;
      end if;
    end loop;
  end loop;
  
  IO.Put_Line("The answer is: "&Integer'Image(answer));
  
end Euler19;