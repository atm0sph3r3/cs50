<?php
    // configuration
    require("../includes/config.php"); 
   
    // Dispaly the user portfolio
    render("portfolio.php", ["title" => "Portfolio","user"=>$user,"results"=>$user->portfolio(),"cashBalance"=>$user->cashBalance()]);
?>
