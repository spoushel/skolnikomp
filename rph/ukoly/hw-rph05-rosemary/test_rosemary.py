from rosemary import Item, update

#name done
def test_normal_name_doesnt_change():
    item = Item('Bread', days_left=3, quality=5)
    update(item)
    return item.name == 'Bread'

def test_diamond_name_doesnt_change():
    item = Item('Diamond', days_left=3, quality=5)
    update(item)
    return item.name == 'Diamond'

def test_brie_name_doesnt_change():
    item = Item('Aged Brie', days_left=3, quality=5)
    update(item)
    return item.name == 'Aged Brie'

def test_tickets_name_doesnt_change():
    item = Item('Tickets', days_left=3, quality=5)
    update(item)
    return item.name == 'Tickets'

#days left done
def test_normal_decreases_days_left():
    item = Item('Bread', days_left=3, quality=5)
    update(item)
    return item.days_left == 2

def test_brie_decreases_days_left():
    item = Item('Aged Brie', days_left=3, quality=5)
    update(item)
    return item.days_left == 2

def test_tickets_decreases_days_left():
    item = Item('Tickets', days_left=3, quality=5)
    update(item)
    return item.days_left == 2

def test_diamond_no_decrease_days_left():
    item = Item('Diamond', days_left=3, quality=100)
    update(item)
    return item.days_left == 3

#quality
#normal
def test_normal_decreases_quality():
    item = Item('Bread', days_left=3, quality=5)
    update(item)
    return item.quality == 4

def test_normal_decreases_quality_0():
    item = Item('Bread', days_left=0, quality=10)
    update(item)
    return item.quality == 8

def test_normal_decreases_quality_expired():
    item = Item('Bread', days_left=-5, quality=5)
    update(item)
    return item.quality == 3

def test_normal_range_quality_low():
    item = Item('Bread', days_left=3, quality=0)
    update(item)
    return item.quality >= 0

#brie
def test_brie_range_quality_high():
    item = Item('Aged Brie', days_left=3, quality=50)
    update(item)
    return item.quality <= 50

def test_brie_increases_quality():
    item = Item('Aged Brie', days_left=5, quality=10)
    update(item)
    return item.quality == 11

def test_brie_increases_quality_0():
    item = Item('Aged Brie', days_left=0, quality=10)
    update(item)
    return item.quality == 11

def test_brie_increases_quality_neg():
    item = Item('Aged Brie', days_left=-5, quality=10)
    update(item)
    return item.quality == 11

#diamond
def test_diamond_quality_stays_100():
    item = Item('Diamond', days_left=5, quality=100)
    update(item)
    return item.quality == 100

#tickets
def test_tickets_range_quality_high():
    item = Item('Tickets', days_left=3, quality=50)
    update(item)
    return item.quality <= 50

def test_tickets_quality_early():
    item = Item('Tickets', days_left=12, quality=10)
    update(item)
    return item.quality == 11

def test_tickets_quality_10():
    item = Item('Tickets', days_left=10, quality=10)
    update(item)
    return item.quality == 12

def test_tickets_quality_medium():
    item = Item('Tickets', days_left=8, quality=10)
    update(item)
    return item.quality == 12

def test_tickets_quality_6():
    item = Item('Tickets', days_left=6, quality=10)
    update(item)
    return item.quality == 12

def test_tickets_quality_soon():
    item = Item('Tickets', days_left=3, quality=10)
    update(item)
    return item.quality == 13

def test_tickets_quality_5():
    item = Item('Tickets', days_left=5, quality=10)
    update(item)
    return item.quality == 13

def test_tickets_quality_over():
    item = Item('Tickets', days_left=0, quality=10)
    update(item)
    return item.quality == 0

def test_tickets_quality_1():
    item = Item('Tickets', days_left=1, quality=10)
    update(item)
    return item.quality == 13

def test_tickets_quality_neg():
    item = Item('Tickets', days_left=-3, quality=10)
    update(item)
    return item.quality == 0
