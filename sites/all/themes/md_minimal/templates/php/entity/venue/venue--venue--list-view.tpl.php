<section itemscope itemtype="http://schema.org/EventVenue" class="clearfix">

    <div class="akordeon-item-head clearfix">
        <div class="akordeon-item-head-container clearfix decolumn_mini">
            <header class="akordeon-heading <?php print $classes; ?>" <?php print $attributes; ?>>
                <h3 class="decolumn_mini">
                    <a class="white" itemprop="name"><?php print $title; ?></a>
                </h3>
                <div class="actions-links fsmall">
                    <span class="action-link">
                        <a class="action-link-view btn btn-success" itemprop="url" href="<?php echo $url; ?>">View Venue</a>
                    </span>
                </div>
            </header>
        </div>
    </div>
    
    <div class="akordeon-item-body">
        <div class="akordeon-item-content">
            <?php print $venue_fields['body']; ?>
        </div>
    </div>
    
</section>