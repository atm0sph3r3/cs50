<? if(isset($name) && isset($symbol) && isset($price)): ?>
    <div id="quote">
        <div>Name: <?= $name ?></div>
        <div>Symbol: <?= $symbol ?></div>
        <div>Price: <?= "$" . number_format((float)$price,3) ?></div>
    </div>
<? else: ?>
    <div>No stock found. Please try again.</div>
<? endif; ?>    
