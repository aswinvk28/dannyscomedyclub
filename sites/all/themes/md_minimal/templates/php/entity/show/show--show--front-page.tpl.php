<section itemscope itemtype="http://schema.org/Event" class="clearfix">

    <div class="akordeon-item-head clearfix">
        <div class="akordeon-item-head-container">
            <header class="akordeon-heading decolumn_mini <?php print $classes; ?>" <?php print $attributes; ?>>
                <h3 class="decolumn_mini">
                    <a href="<?php echo $url; ?>" class="white" itemprop="name"><?php print $title; ?></a>
                </h3>
                <div class="actions-links fsmall">
                    <span class="action-link">
                        <a class="action-link-view btn btn-warning" itemprop="url" href="<?php echo $url; ?>">View Show</a>
                    </span>
                </div>
            </header>
        </div>
    </div>
    
    <div class="akordeon-item-body">
        <div class="akordeon-item-content">
            <div class="white column_small decolumn_mini" itemtype="http://schema.org/EventVenue" itemprop="location" itemscope>
            <?php if(!empty($venue['title']) && !empty($venue['path'])) { ?>
                <span>Venue: </span>
                <span><a itemprop="url" href="<?php print $venue['path']; ?>"><span itemprop="name"><?php print $venue['title']; ?><span></a></span>
            <?php } ?>
            </div>
            <?php $performances = render($published_performances);
            print $performances;
            if(empty($performances)) { ?>
            <p class="column_mini clearfix align-center">Acts to be confirmed shortly!</p>
            <?php } ?>
        </div>
    </div>
    
</section>