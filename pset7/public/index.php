<?php
    // configuration
    require("../includes/config.php"); 
   
    // Dispaly the user portfolio using a User object
    $user = User::getUser();
    render("portfolio.php", ["title" => "Portfolio","user"=>$user,"results"=>$user->portfolio()]);
?>
