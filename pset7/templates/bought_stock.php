<? 
if(isset($results)):
    extract($results);
?> 
<div id="purchase">
    <div>
        Stock purchased: <?= $symbol ?>
    </div>
    <div>
        Shares purchased: <?= $shares ?>
    </div>
    <div>
        Share price: <?= numberFormat($price) ?>
    </div>
    <div>
        Total cost: <?= numberFormat($cost) ?>
    </div>
</div>
<?
endif;
?>

