<?php
    require("../includes/config.php");
    
    //User is searching for a stock
    if(isset($_GET["submit"])){
        $quote = lookup($_GET["stock"]);
        if($quote !== false){
            render("searchResult.php", array("stock"=>$_GET["stock"], "quote"=>$_GET[$quote], "success"=>true));
        } else {
            render("displaySearch.php");
        }
    } else {
        render("../templates/search");
    }