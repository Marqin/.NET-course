Module PrimeClient

    Sub Main()
        Dim PrimeLib As PrimeServerLib.Prime
        PrimeLib = New PrimeServerLib.Prime()


        For i As Integer = 0 To 20
            If PrimeLib.IsPrime(i) > 0 Then
                System.Console.WriteLine(i & " is a prime!")
            Else
                System.Console.WriteLine(i & " is not a prime!")
            End If
        Next


    End Sub

End Module
