--Project Euler #3
--The prime factors of 13195 are 5, 7, 13 and 29.
--What is the largest prime factor of the number 600851475143

with Ada.Text_IO; use Ada.Text_IO;

procedure Euler3 is

  package IO renames Ada.Text_IO;

  --Variable declarations
  answer : Long_Long_Integer := 0;
  value : Long_Long_Integer := 600851475143;
  Z : Long_Long_Integer := 2;
  
begin

  While_Loop:
  while (Z * Z <= value) loop
    if value mod Z = 0 then
      if Z > answer then
       answer := Z;
      end if;
      value := value / Z;
    else
      Z := Z + 1;
    end if;
  end loop While_Loop;

  if value > 1 then
    if value > answer then
     answer := value;
    end if;
  end if;

  IO.Put_Line("The answer is: " & Long_Long_Integer'Image(answer));
  
end Euler3;