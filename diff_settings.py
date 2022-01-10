#!/usr/bin/env python3

def apply(config, args):
    config['mapfile'] = f'build/mario-paint.map'
    config['myimg'] = f'build/mario-paint.z64dd'
    config['baseimg'] = f'mario-paint.bin'
    config['source_directories'] = ['src', 'include', 'asm']
