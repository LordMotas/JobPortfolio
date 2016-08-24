--Project Euler #8
--Find the thirteen adjacent digits in the 1000-digit number
--that have the greatest product.
--what is the value of this product?

with Ada.Text_IO; use Ada.Text_IO;

procedure Euler8 is

  package IO renames Ada.Text_IO;
  package IIO renames Ada.Integer_Text_IO;

  --Variable declarations
  answer : Integer := 0;
  ThousandDigit : String (1..1000) := "7316717653133062491922511967442657474235534919493496983520312774506326239578318016984801869478851843858615607891129494954595017379583319528532088055111254069874715852386305071569329096329522744304355766896648950445244523161731856403098711121722383113622298934233803081353362766142828064444866452387493035890729629049156044077239071381051585930796086670172427121883998797908792274921901699720888093776657273330010533678812202354218097512545405947522435258490771167055601360483958644670632441572215539753697817977846174064955149290862569321978468622482839722413756570560574902614079729686524145351004748216637048440319989000889524345065854122758866688116427171479924442928230863465674813919123162824586178664583591245665294765456828489128831426076900422421902267105562632111110937054421750694165896040807198403850962455444362981230987879927244284909188845801561660979191338754992005240636899125607176060588611646710940507754100225698315520005593572972571636269561882670428252483600823257530420752963450";
  PlaceHolder : Integer := 0;

begin
  for J in 0..987 loop
    PlaceHolder := (Integer'Value(ThousandDigit(ThousandDigit'First+J..ThousandDigit'First+J))) * (Integer'Value(ThousandDigit(ThousandDigit'First+J+1..ThousandDigit'First+J+1))) * (Integer'Value(ThousandDigit(ThousandDigit'First+J+2..ThousandDigit'First+J+2))) * (Integer'Value(ThousandDigit(ThousandDigit'First+J+3..ThousandDigit'First+J+3))) * (Integer'Value(ThousandDigit(ThousandDigit'First+J+4..ThousandDigit'First+J+4))) * (Integer'Value(ThousandDigit(ThousandDigit'First+J+5..ThousandDigit'First+J+5))) * (Integer'Value(ThousandDigit(ThousandDigit'First+J+6..ThousandDigit'First+J+6))) * (Integer'Value(ThousandDigit(ThousandDigit'First+J+7..ThousandDigit'First+J+7))) * (Integer'Value(ThousandDigit(ThousandDigit'First+J+8..ThousandDigit'First+J+8))) * (Integer'Value(ThousandDigit(ThousandDigit'First+J+9..ThousandDigit'First+J+9))) * (Integer'Value(ThousandDigit(ThousandDigit'First+J+10..ThousandDigit'First+J+10))) * (Integer'Value(ThousandDigit(ThousandDigit'First+J+11..ThousandDigit'First+J+11))) * (Integer'Value(ThousandDigit(ThousandDigit'First+J+12..ThousandDigit'First+J+12))); 
    if PlaceHolder > answer then
      IO.Put_Line(Integer'Image(PlaceHolder));
      answer := PlaceHolder;
    end if;
  end loop;
IO.Put_Line("The answer is: " & Integer'Image(answer));

end Euler8;