<?php
    require("../includes/config.php");
    
    //User is searching for a stock
    if(isset($_GET["submit"])){
        $quote = lookup($_GET["stock"]);
        if($quote !== false){
            render("stock_result.php", array("symbol"=>$quote['symbol'], "name"=>$quote['name'], "price"=>$quote['price'], "title"=>$quote['symbol']."information"));
        } else {
            render("stock_result.php",array("title"=>"No results to display."));
        }
    } else {
        render("stock_lookup.php",array("title"=>"Look-up Stock Price"));
    }