<?php

/**
 * Description of quote
 *
 * @author dev
 */
class quoteModel extends Model {
    
    public function __construct() {
        //no code
    }
    
    //Method to lookup stock quote
    public function lookup($stock){
       return lookup($stock);
    }
        
}
