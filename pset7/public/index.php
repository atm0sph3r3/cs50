<?php
    // configuration
    require("../includes/config.php"); 
    require("../models/account_info.php");
    
    if(isset($_SESSION['id'])){
        //Get porfolio information from models/account_info.php
        $returnResults = generatePortfolio();
        // render portfolio
        render("portfolio.php", ["title" => "Portfolio","results"=>$returnResults]);
    } else {
        redirect("login_form.php");
    }
    
?>
